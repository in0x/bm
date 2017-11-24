// Fill out your copyright notice in the Description page of Project Settings.

#include "BmGameMode.h"
#include "BmPlayerCharacter.h"
#include "BmPlayerController.h"
#include "BmCameraActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ABmGameMode::ABmGameMode(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
	, cameraActorInstance(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

APawn* ABmGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	ABmPlayerController* bmController = CastChecked<ABmPlayerController>(NewPlayer);

	int32 controllerID = UGameplayStatics::GetPlayerControllerID(bmController);
	checkf(inputBindings.Num() > controllerID, TEXT("Trying to bind input for controller with ID %d, but only %d Input Bindings exist."), controllerID, inputBindings.Num());
	bmController->SetInputBindingNames(inputBindings[controllerID]);

	APawn* defaultPlayer = Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
	bmController->SetupInputComponent();

	return defaultPlayer;
}

APlayerController* ABmGameMode::SpawnPlayerController(ENetRole InRemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
	APlayerController* spawnedController = Super::SpawnPlayerController(InRemoteRole, SpawnLocation, SpawnRotation);
	return spawnedController;
}

void ABmGameMode::StartPlay() 
{
	Super::StartPlay();
}

void ABmGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TObjectIterator<ABmCameraActor> iter; iter; ++iter)
	{
		if (iter->ActorHasTag("MainCamera"))
		{
			cameraActorInstance = *iter;
		}
	}

	checkf(cameraActorInstance != nullptr, TEXT("No BmCameraActor marked with MainCamera tag found."));

	CreatePlayer(0);
	CreatePlayer(1);
}

void ABmGameMode::Tick(float DeltaSeconds)
{
	bool bAnyPlayerDied = false;
	bool bAllPlayersDied = true;

	for (ABmPlayerCharacter* player : players)
	{
		bAnyPlayerDied |= !player->IsAlive();
		bAllPlayersDied &= !player->IsAlive();
	}

	if (bAllPlayersDied)
	{
		GameEndedDraw();
	}
	else if (bAnyPlayerDied)
	{
		int32 idxOfDeadPlayer = players.IndexOfByPredicate([](ABmPlayerCharacter* Player) { return Player->IsAlive(); });
		GameEndedWin(idxOfDeadPlayer); 
	}

	if (bAllPlayersDied || bAnyPlayerDied)
	{
		for (ABmPlayerCharacter* player : players)
		{
			APlayerController* ctrl = CastChecked<APlayerController>(player->GetController());
			if (ctrl != nullptr)
			{
				ctrl->DisableInput(ctrl);

				ctrl->bShowMouseCursor = true;
				ctrl->bEnableClickEvents = true;
				ctrl->bEnableMouseOverEvents = true;
			}
		}
	}
}

void ABmGameMode::RestartGame()
{
	GetWorld()->ServerTravel("?Restart");
}

void ABmGameMode::CreatePlayer(int32 ControllerID)
{
	APlayerController* spawnedController = UGameplayStatics::GetPlayerController(GetWorld(), ControllerID);

	if (spawnedController == nullptr)
	{
		spawnedController = UGameplayStatics::CreatePlayer(GetWorld(), ControllerID, true);
	}

	ABmPlayerCharacter* player = CastChecked<ABmPlayerCharacter>(spawnedController->GetCharacter());
	player->AutoPossessPlayer = EAutoReceiveInput::Player0;
	cameraActorInstance->RegisterControllerToTrack(spawnedController);
	players.Add(player);
}

void ABmGameMode::GameEndedDraw_Implementation()
{
}

void ABmGameMode::GameEndedWin_Implementation(int32 WinningPlayerID)
{
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "BmGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ABmGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABmGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
	APlayerController* spawnedController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	spawnedController->GetCharacter()->AutoPossessPlayer = EAutoReceiveInput::Player0;
}




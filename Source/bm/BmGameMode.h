// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BmInputBinding.h"
#include "BmGameMode.generated.h"

class ABmCameraActor;

UCLASS()
class BM_API ABmGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABmGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation) override;

private:
	void CreatePlayer(int32 ControllerID);

	UPROPERTY(EditAnywhere)
	TArray<FBmInputBinding> inputBindings;

	UPROPERTY(Transient)
	ABmCameraActor* cameraActorInstance;
};

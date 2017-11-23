// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BmCameraActor.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BM_API ABmCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABmCameraActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void RegisterControllerToTrack(APlayerController* controller);

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* springArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere)
	float minCameraHeight;

	UPROPERTY(EditAnywhere)
	float maxCameraHeight;

	UPROPERTY(Transient)
	TArray<APlayerController*> trackedControllers;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "BmCameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ABmCameraActor::ABmCameraActor(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	springArmComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));

	springArmComponent->SetupAttachment(GetRootComponent());
	cameraComponent->SetupAttachment(springArmComponent);

	SetRootComponent(springArmComponent);
}

void ABmCameraActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABmCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector playerPosition = FVector::ZeroVector;

	for (APlayerController* tracked : trackedControllers)
	{
		playerPosition += tracked->GetFocalLocation();
	}

	float longestDistance = minCameraHeight;
	int32 numControllers = trackedControllers.Num();

	for (int32 i = 1; i < numControllers; ++i)
	{
		float distance = FVector::Dist(trackedControllers[i]->GetFocalLocation(), trackedControllers[i - 1]->GetFocalLocation());
		longestDistance = FMath::Max(longestDistance, distance);
	}
	longestDistance = FMath::Min(longestDistance, maxCameraHeight);

	FVector selfPosition = GetActorLocation();
	playerPosition /= trackedControllers.Num();
	RootComponent->SetWorldLocation(FVector(playerPosition.X, playerPosition.Y, longestDistance));
}

void ABmCameraActor::RegisterControllerToTrack(APlayerController* controller)
{
	controller->SetViewTargetWithBlend(this);
	trackedControllers.Add(controller);
}



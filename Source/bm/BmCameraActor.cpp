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
}

void ABmCameraActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetViewTargetWithBlend(this);
}

void ABmCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector selfPosition = GetActorLocation();
	FVector playerPosition = controller->GetFocalLocation();

	RootComponent->SetWorldLocation(FVector(playerPosition.X, playerPosition.Y, selfPosition.Z));
}


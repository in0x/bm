// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABmPlayerCharacter::ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	PrimaryActorTick.bCanEverTick = true;
	
	cameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	springArmComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));

	springArmComponent->SetupAttachment(GetRootComponent());
	cameraComponent->SetupAttachment(springArmComponent);
}

void ABmPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ABmPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABmPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABmPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABmPlayerCharacter::MoveRight);
}

void ABmPlayerCharacter::MoveForward(float Value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, Value);
}

void ABmPlayerCharacter::MoveRight(float Value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, Value);
}
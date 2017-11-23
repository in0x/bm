// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerController.h"
#include "BmInputBinding.h"

void ABmPlayerController::SetInputBindingNames(const FBmInputBinding& Bindings)
{
	MoveForwardBindingName = Bindings.moveForwardBindName;
	MoveRightBindingName = Bindings.moveRightBindName;
	PlaceBombBindingName = Bindings.placeBombBindName;
}

void ABmPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveForwardBindingName, this, &ABmPlayerController::MoveForward);
	InputComponent->BindAxis(MoveRightBindingName, this, &ABmPlayerController::MoveRight);
}

void ABmPlayerController::MoveForward(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	GetPawn()->AddMovementInput(direction, Value);
}

void ABmPlayerController::MoveRight(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	GetPawn()->AddMovementInput(direction, Value);
}
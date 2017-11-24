// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerController.h"
#include "BmPlayerCharacter.h"
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

	InputComponent->BindAxis(MoveForwardBindingName, this, &ABmPlayerController::OnMoveForward);
	InputComponent->BindAxis(MoveRightBindingName, this, &ABmPlayerController::OnMoveRight);
	InputComponent->BindAction(PlaceBombBindingName, EInputEvent::IE_Pressed, this, &ABmPlayerController::OnPlaceBomb);
}

void ABmPlayerController::OnMoveForward(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	GetPawn()->AddMovementInput(direction, Value);
}

void ABmPlayerController::OnMoveRight(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	GetPawn()->AddMovementInput(direction, Value);
}

void ABmPlayerController::OnPlaceBomb()
{
	ABmPlayerCharacter* player = CastChecked<ABmPlayerCharacter>(GetPawn());
	player->PlaceBomb();
}

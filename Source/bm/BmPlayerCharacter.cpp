// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABmPlayerCharacter::ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABmPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ABmPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector movement = GetMovementComponent()->GetLastInputVector();
	movement.Normalize();

	if (movement.SizeSquared() > 0.f)
	{
		float yaw = movement.HeadingAngle();
		yaw = UKismetMathLibrary::RadiansToDegrees(yaw);
		FRotator rotation(0.f, yaw, 0.f);

		GetRootComponent()->SetWorldRotation(rotation);
	}
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
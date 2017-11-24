// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerCharacter.h"
#include "Bomb/BmBaseBombActor.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABmPlayerCharacter::ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
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

void ABmPlayerCharacter::SetBombClass(TSubclassOf<ABmBaseBombActor> BombClass)
{
	bombClass = BombClass;
}

void ABmPlayerCharacter::PlaceBomb()
{
	if (RemoteBombTriggered.IsBound())
	{
		RemoteBombTriggered.Broadcast(placedBombs.Pop());
	}

	if (placedBombs.Num() >= maxBombCount)
	{
		return;
	}

	FVector forward = GetActorForwardVector();
	FVector location = GetActorLocation();

	ABmBaseBombActor* spawnedActor = GetWorld()->SpawnActorDeferred<ABmBaseBombActor>(bombClass.Get(), GetTransform(), nullptr, this);

	placedBombs.Add(spawnedActor);
	spawnedActor->BombExploded.AddDynamic(this, &ABmPlayerCharacter::OnBombExploded);

	spawnedActor->FinishSpawning(GetTransform());
}

void ABmPlayerCharacter::OnBombExploded(ABmBaseBombActor* ExplodedBomb)
{
	ExplodedBomb->BombExploded.RemoveDynamic(this, &ABmPlayerCharacter::OnBombExploded);
	placedBombs.Remove(ExplodedBomb);
}

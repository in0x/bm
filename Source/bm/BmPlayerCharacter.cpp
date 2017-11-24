// Fill out your copyright notice in the Description page of Project Settings.

#include "BmPlayerCharacter.h"
#include "HealthComponent.h"
#include "Bomb/BmBaseBombActor.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"

ABmPlayerCharacter::ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
	, overridenBombRange(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	bCanBeDamaged = true;

	healthComponent = ObjectInitializer.CreateDefaultSubobject<UHealthComponent>(this, TEXT("HealthComponent"));
}

void ABmPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	materialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	materialInstance->SetVectorParameterValue(FName("BodyColor"), FMath::VRand());
}

void ABmPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector movement = GetMovementComponent()->GetLastInputVector();
	movement.Normalize();

	if (movement.SizeSquared() > 0.0f)
	{
		float yaw = movement.HeadingAngle();
		yaw = UKismetMathLibrary::RadiansToDegrees(yaw);
		FRotator rotation(0.0f, yaw, 0.0f);

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
	FVector location =  GetActorLocation();
	location.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	FTransform transform = GetTransform();
	transform.SetLocation(location);

	ABmBaseBombActor* spawnedActor = GetWorld()->SpawnActorDeferred<ABmBaseBombActor>(bombClass.Get(), transform, nullptr, this);

	placedBombs.Add(spawnedActor);
	spawnedActor->BombExploded.AddDynamic(this, &ABmPlayerCharacter::OnBombExploded);

	if (overridenBombRange > 0.0f)
	{
		spawnedActor->SetExplodeRange(overridenBombRange);
	}

	spawnedActor->FinishSpawning(transform);
}

void ABmPlayerCharacter::OnBombExploded(ABmBaseBombActor* ExplodedBomb)
{
	ExplodedBomb->BombExploded.RemoveDynamic(this, &ABmPlayerCharacter::OnBombExploded);
	placedBombs.Remove(ExplodedBomb);
}

int32 ABmPlayerCharacter::GetMaxBombCount()
{
	return maxBombCount;
}

void ABmPlayerCharacter::SetMaxBombCount(int32 Count)
{
	maxBombCount = Count;
}

void ABmPlayerCharacter::SetBombRangeOverride(float BombRange)
{
	overridenBombRange = BombRange;
}

bool ABmPlayerCharacter::IsAlive()
{
	return healthComponent->GetHealthPercent() > 0.0f;
}


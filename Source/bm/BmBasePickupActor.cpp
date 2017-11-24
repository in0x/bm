// Fill out your copyright notice in the Description page of Project Settings.

#include "BmBasePickupActor.h"
#include "BmPlayerCharacter.h"
#include "HealthComponent.h"

namespace
{
	const FName PICKUP_COLLISION_PROFILE_NAME("OverlapAll");
}

ABmBasePickupActor::ABmBasePickupActor(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UStaticMeshComponent* meshComponent = GetStaticMeshComponent();

	meshComponent->bGenerateOverlapEvents = true;
	meshComponent->bMultiBodyOverlap = true;
	meshComponent->SetCollisionProfileName(PICKUP_COLLISION_PROFILE_NAME);

	meshComponent->SetSimulatePhysics(false);

	healthComponent = ObjectInitializer.CreateDefaultSubobject<UHealthComponent>(this, TEXT("HealthComponent"));

	bCanBeDamaged = true;
}

void ABmBasePickupActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABmBasePickupActor::OnBeginOverlap);
	healthComponent->MinHealthReached.AddDynamic(this, &ABmBasePickupActor::OnKilled);
}

void ABmBasePickupActor::OnCharacterPickedUp_Implementation(ABmPlayerCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, *FString::Printf(TEXT("%s picked up by %s."), *GetName(), *Character->GetName()));
}

void ABmBasePickupActor::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ABmPlayerCharacter>())
	{
		OnCharacterPickedUp(CastChecked<ABmPlayerCharacter>(OtherActor));
	}
}

void ABmBasePickupActor::OnKilled()
{
	Destroy();
}




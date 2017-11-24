// Fill out your copyright notice in the Description page of Project Settings.

#include "BmBasePickupActor.h"
#include "BmPlayerCharacter.h"

namespace
{
	const FName PICKUP_COLLISION_PROFILE_NAME("OverlapAll");
}

ABmBasePickupActor::ABmBasePickupActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UStaticMeshComponent* meshComponent = GetStaticMeshComponent();

	meshComponent->bGenerateOverlapEvents = true;
	meshComponent->bMultiBodyOverlap = true;
	meshComponent->SetCollisionProfileName(PICKUP_COLLISION_PROFILE_NAME);

	meshComponent->SetSimulatePhysics(false);
}

void ABmBasePickupActor::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ABmBasePickupActor::OnBeginOverlap);
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





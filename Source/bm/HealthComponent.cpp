// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
	: Super()
	, health(100.f)
	, minHealth(0.f)
	, maxHealth(100.f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::IncreaseHealth(float Value)
{
	health = FMath::Max(minHealth, health - Value);

	if (health <= minHealth)
	{
		MinHealthReached.Broadcast();
	}
}

void UHealthComponent::DecreaseHealth(float Value)
{
	health = FMath::Min(maxHealth, health + Value);
}

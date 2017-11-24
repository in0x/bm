// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMinHealthReached);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void DecreaseHealth(float Value);

	UPROPERTY(BlueprintAssignable)
	FMinHealthReached MinHealthReached;

private:
	UPROPERTY(EditAnywhere)
	float health;

	UPROPERTY(EditAnywhere)
	float minHealth;

	UPROPERTY(EditAnywhere)
	float maxHealth;
};
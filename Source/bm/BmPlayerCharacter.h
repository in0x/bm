// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BmPlayerCharacter.generated.h"

class ABmBaseBombActor;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemoteBombTriggered, ABmBaseBombActor*, TriggeredBomb);

UCLASS()
class BM_API ABmPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void PlaceBomb();

	UPROPERTY(BlueprintAssignable)
	FRemoteBombTriggered RemoteBombTriggered;

	UFUNCTION(BlueprintCallable)
	void SetBombClass(TSubclassOf<ABmBaseBombActor> BombClass);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxBombCount();

	UFUNCTION(BlueprintCallable)
	void SetMaxBombCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void SetBombRangeOverride(float BombRange);

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

private:
	UFUNCTION()
	void OnBombExploded(ABmBaseBombActor* ExplodedBomb);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABmBaseBombActor> bombClass;

	UPROPERTY(EditAnywhere)
	UHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere)
	int32 maxBombCount;

	UPROPERTY(EditAnywhere)
	float overridenBombRange;
	
	UPROPERTY()
	TArray<ABmBaseBombActor*> placedBombs;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BmBaseBombActor.generated.h"

class UHealthComponent;

UCLASS()
class BM_API ABmBaseBombActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBombExploded, ABmBaseBombActor*, ExplodedBomb);

	ABmBaseBombActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetExplodeRange(float Range);

	UPROPERTY(BlueprintAssignable)
	FBombExploded BombExploded;
	
protected:
	UFUNCTION(BlueprintNativeEvent)
	void Explode();

	UFUNCTION(BlueprintCallable)
	void Explode_Implementation();

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float explodeRange;

	TArray<FHitResult> Trace(UWorld* world, FVector Start, FVector End, const TArray<TWeakObjectPtr<AActor>>& IgnoredActors) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* healthComponent;

private:
	UFUNCTION()
	void OnKilled();

	bool bExplodeNextTick;
};

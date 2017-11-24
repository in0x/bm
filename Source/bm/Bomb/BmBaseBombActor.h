// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BmBaseBombActor.generated.h"

UCLASS()
class BM_API ABmBaseBombActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBombExploded, ABmBaseBombActor*, ExplodedBomb);

	ABmBaseBombActor();

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
};

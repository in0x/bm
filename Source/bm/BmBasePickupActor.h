// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BmBasePickupActor.generated.h"

class UHealthComponent;
class ABmPlayerCharacter;

UCLASS()
class BM_API ABmBasePickupActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ABmBasePickupActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnCharacterPickedUp(ABmPlayerCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* healthComponent;

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnKilled();
};

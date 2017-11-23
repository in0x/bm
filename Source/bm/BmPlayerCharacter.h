// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BmPlayerCharacter.generated.h"

UCLASS()
class BM_API ABmPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};

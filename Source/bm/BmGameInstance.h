// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BmGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BM_API UBmGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBmGameInstance();

	UPROPERTY(BlueprintReadWrite)
	int32 roundsPlayed;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> playerScores;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BmInputBinding.generated.h"

USTRUCT(BlueprintType)
struct FBmInputBinding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName moveForwardBindName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName moveRightBindName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName placeBombBindName;
};
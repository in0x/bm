// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BmPlayerController.generated.h"

struct FBmInputBinding;

UCLASS()
class BM_API ABmPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetInputBindingNames(const FBmInputBinding& Bindings);

	virtual void SetupInputComponent() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	FName MoveForwardBindingName;
	FName MoveRightBindingName;
	FName PlaceBombBindingName;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BmPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BM_API ABmPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABmPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* springArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* cameraComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"


class APlayerCharacter;

UCLASS()
class ASSIGNMENT1_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
		float MouseSensitivity = 2.0f;
	virtual void SetupInputComponent();
	virtual void CallForwards(float Value);
	virtual void CallRight(float Value);
	virtual void CallLookUp(float Value);
	virtual void CallTurn(float Value);
	APlayerCharacter* MyPawn;
	
};

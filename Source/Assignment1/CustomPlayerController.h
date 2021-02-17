// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"


class APlayerCharacter;
class UUserWidget;

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
	virtual void CallForwards(float Value); // tells the custom movement component of the pawn to move the character on its local forward-facing axis
	virtual void CallRight(float Value); // tells the custom movement component of the pawn to move the character on its right-facing axis
	virtual void CallLookUp(float Value); // tells the custom movement component of the pawn to rotate the springarm on the local x axis
	virtual void CallTurn(float Value); // tells the custom movement component of the pawn to rotate the character on the Z axis
	virtual void CallFire(); // shoots a projectile from the player character
	APlayerCharacter* MyPawn;

	// UI code
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass; 
	UPROPERTY()
		UUserWidget* UIInstance;
	UPROPERTY()
		float healthPercentage = 1.0f;
	UFUNCTION(BlueprintPure)
		float GetHealthPercentage();
	UPROPERTY()
		int ammoCount = 15;
	UPROPERTY()
		int maxAmmoCount = 15;
	UFUNCTION(BlueprintPure)
		float GetAmmoPercent();
};

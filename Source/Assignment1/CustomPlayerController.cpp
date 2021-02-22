// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "PlayerCharacter.h"
#include "CustomMovementComponent.h"
#include "Blueprint/UserWidget.h"

void ACustomPlayerController::BeginPlay() {
	Super::BeginPlay();
	MyPawn = Cast<APlayerCharacter>(GetPawn());
	UIInstance = CreateWidget(this, HUDClass);
	if(UIInstance != nullptr)
		UIInstance->AddToViewport();
}
void ACustomPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	check(InputComponent);

	// get the axis mappings and bind them to functions in this class
	InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::CallForwards);
	InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::CallRight);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::CallLookUp);
	InputComponent->BindAxis("Turn", this, &ACustomPlayerController::CallTurn);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallFire);

}

// *********************************
//      player movement:  get the movement component and call the function to move the player, pass on the 'Value' parameter
// *********************************
void ACustomPlayerController::CallForwards(float Value)
{
	if (MyPawn) {
		MyPawn->PawnMovement->MoveForward(Value);
	}

}
void ACustomPlayerController::CallRight(float Value)
{
	if (MyPawn) {
		MyPawn->PawnMovement->MoveRight(Value);
	}
}
void ACustomPlayerController::CallLookUp(float Value)
{
	if (MyPawn) {
		MyPawn->PawnMovement->LookUp(Value*MouseSensitivity);
	}
}
void ACustomPlayerController::CallTurn(float Value)
{
	if (MyPawn) {
		MyPawn->PawnMovement->Turn(Value);
	}
}

// when the player presses the fire button, call the fire function in the movement class and decrease the players ammo count
void ACustomPlayerController::CallFire()
{
	if (ammoCount > 0)
	{
		if (MyPawn) {
			MyPawn->PawnMovement->Fire();
			ammoCount--;
		}
	}
}

// called by the UI
// sets the health bar based on the percentage of health the player has
float ACustomPlayerController::GetHealthPercentage()
{
	return MyPawn->Health / MyPawn->maxHealth;
}
// gets the ammo bar based on the percentage of ammo the player has left
float ACustomPlayerController::GetAmmoPercent()
{
	return (float)ammoCount /(float)maxAmmoCount;
}
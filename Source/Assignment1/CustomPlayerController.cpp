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
	InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::CallForwards);
	InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::CallRight);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::CallLookUp);
	InputComponent->BindAxis("Turn", this, &ACustomPlayerController::CallTurn);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallFire);

}
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

float ACustomPlayerController::GetHealthPercentage()
{
	return healthPercentage;
}
float ACustomPlayerController::GetAmmoPercent()
{
	return (float)ammoCount /(float)maxAmmoCount;
}
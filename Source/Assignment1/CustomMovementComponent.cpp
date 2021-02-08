// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovementComponent.h"
#include <Assignment1\PlayerCharacter.h>
#include <GameFramework/SpringArmComponent.h>

// Sets default values for this component's properties
UCustomMovementComponent::UCustomMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCustomMovementComponent::MoveForward(float AxisX)
{
	/*FVector DeltaLocation = FVector(AxisX * MoveSpeed * GetWorld()->DeltaTimeSeconds,
		0.0f, 0.0f);
	GetOwner()->AddActorLocalOffset(DeltaLocation, true);*/

	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	character->AddMovementInput(character->GetActorForwardVector()*AxisX);


}

void UCustomMovementComponent::MoveRight(float AxisZ)
{
	// using AddMovementInput plays the animations on the character, so i switched to using that instead
	/*float RotateAmount = AxisZ * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.0f, RotateAmount, 0.0f);
	FQuat DeltaRotation = FQuat(Rotation);
	GetOwner()->AddActorLocalRotation(DeltaRotation, true);*/


	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	character->AddMovementInput(character->GetActorRightVector() * AxisZ);
}
void UCustomMovementComponent::LookUp(float MouseY)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	FRotator newRotation = FRotator(-MouseY, 0.0f, 0.0f);
	character->springArm->AddLocalRotation(newRotation.Quaternion());
}
void UCustomMovementComponent::Turn(float MouseY)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	character->AddControllerYawInput(MouseY);
}



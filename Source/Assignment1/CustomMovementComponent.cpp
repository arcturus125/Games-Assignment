// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovementComponent.h"
#include <Assignment1\PlayerCharacter.h>
#include <GameFramework/SpringArmComponent.h>

#include "Bullet.h"

// Sets default values for this component's properties
UCustomMovementComponent::UCustomMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UCustomMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ****************************************
//          movement: get a reference to the character and move/rotate it based on inputs
// ****************************************
void UCustomMovementComponent::MoveForward(float AxisX)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	character->AddMovementInput(character->GetActorForwardVector()*AxisX);
}
void UCustomMovementComponent::MoveRight(float AxisZ)
{
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


// when the player presses the shoot button, get the position and rotation from the local space of the bluprint
// spawn the bullet, and set the owner of the bullet
// then play the shooting sound
void UCustomMovementComponent::Fire()
{
	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());
	//checks teabag projectile has been set in the editor
	if (character->bulletClass) 
	{ 
		FVector SpawnLocation = character->projectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = character->projectileSpawnPoint->GetComponentRotation();
		ABullet* TempBullet= GetWorld()->SpawnActor<ABullet>(character->bulletClass, SpawnLocation, SpawnRotation);
		TempBullet->SetOwner(character);
		TempBullet->PlayShootSound();
	}
	
}



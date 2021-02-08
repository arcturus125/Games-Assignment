// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCustomMovementComponent;
class ABullet;



UCLASS()
class ASSIGNMENT1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(EditAnywhere)
		UCustomMovementComponent* PawnMovement;
	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;




private:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> BulletClass;
public:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;

};

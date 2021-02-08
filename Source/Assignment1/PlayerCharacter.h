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

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// accessed in CustomMovementComponent.cpp
	UPROPERTY(EditAnywhere)
		UCustomMovementComponent* PawnMovement;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> bulletClass;
	UPROPERTY(EditAnywhere)
		USceneComponent* projectileSpawnPoint;
private:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;


	void Fire();

};

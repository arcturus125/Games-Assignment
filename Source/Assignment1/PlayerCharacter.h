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
	// accessed in CustomMovementComponent.cpp
	UPROPERTY(EditAnywhere)
		UCustomMovementComponent* PawnMovement;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> bulletClass;
	UPROPERTY(EditAnywhere)
		USceneComponent* projectileSpawnPoint;


	float Health = 100;
	float maxHealth = 100;
private:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	void Fire();

	// allows the player to take damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"
class ABullet;

UCLASS()
class ASSIGNMENT1_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void ShootPlayer();

	UPROPERTY(EditAnywhere)
		USceneComponent* projectileSpawnPoint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> bulletClass; // reference to the bullet class so the enemy can shoot bullets
	UPROPERTY(EditAnywhere)
		AActor* lookoutPoint;	// 
	UPROPERTY(EditAnywhere)		// these are the two points the enemy will patrol between if they have not sighted the player
		AActor* homePoint;		//
private:
	// health of the enemy: assigned in world outliner (enemies will have more health on later levels)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Health = 10.0f;

	// code that allows the enemies to take damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
};

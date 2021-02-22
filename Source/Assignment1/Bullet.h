// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class ASSIGNMENT1_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();
private:
	UPROPERTY(Editanywhere)
		UProjectileMovementComponent* projectileMovement;
	UPROPERTY(EditAnywhere)
		USoundBase* deathSound; // set in blueprint, plays when bullet hits an enemy or player
	UPROPERTY(EditAnywhere)
		USoundBase* shootSound; // set in blueprint, plays when bullet is shot

	UPROPERTY(EditAnywhere)
		float movementSpeed = 1000.0f; // speed of the bullet
	UPROPERTY(EditAnywhere)
		float bulletDamage = 10.0f; // damage of the bullet
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* bulletMesh; // mesh of the bullet 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// called in the enemy and player character classes, needs to be public
	void PlayShootSound();



	//collision management
private:
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);
};

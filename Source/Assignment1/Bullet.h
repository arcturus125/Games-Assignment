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
		UProjectileMovementComponent* projectileMovement;/*
	UPROPERTY(Editanywhere)
		UBoxComponent* collider;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float movementSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		float bulletDamage = 10.0f;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* bulletMesh;
//
//
//	//collision management
//private:
//	UFUNCTION()
//		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//			FVector NormalImpulse, const FHitResult& Hit);
//
//	UFUNCTION()
//		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
//			AActor* OtherActor,
//			UPrimitiveComponent* OtherComp,
//			int32 OtherBodyIndex,
//			bool bFromSweep,
//			const FHitResult& SweepResult);

};

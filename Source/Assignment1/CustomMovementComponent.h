// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT1_API UCustomMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float MouseY);
	void Turn(float MouseX);
	void Fire();
private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 500.0f;

		
};

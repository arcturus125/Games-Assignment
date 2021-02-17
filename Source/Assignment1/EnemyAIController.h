// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY()
	TArray<AActor*> Waypoints;
	UPROPERTY()
		AActor* lookoutPoint;
	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehaviorTree;
	AActor* ChooseWaypoint();
	void RandomPatrol();
	APawn* PlayerPawn;
public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	void LOScheck();
};

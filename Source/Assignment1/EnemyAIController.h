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
public:
	virtual void BeginPlay() override;
	void StartTree();
private:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehaviorTree;

	/* the points that the enemy patrols between are no longer assigned via code, and are instead
	* assigned per enemy; this means two different enemies can have different patrol points
	*/
};

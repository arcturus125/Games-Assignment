// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_API ACustomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void TriggerLevelChange(FName levelName, int killsNeededOnNextLevel);
	UPROPERTY(EditAnywhere)  // different levels will have a different required number of kills, will be changed in the world outliner
		int requiredNumOfKills = 2;
	int numOfEnemiesKilled = 0; //needs to be public, accessedin enemycharacter when an enemy dies
private:
	virtual void BeginPlay() override;
	void Start();
	void TimerUp();


	
};

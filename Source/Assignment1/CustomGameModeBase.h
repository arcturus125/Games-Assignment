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
	void TriggerLevelChange(FName levelName);
	int numOfEnemiesKilled = 0;
	int requiredNumOfKills = 2;
	virtual void BeginPlay() override;
	void Start();
	void TimerUp();

	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"
#include <Kismet/GameplayStatics.h>


FTimerHandle EndGameTimer;

void ACustomGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Start();
}
void ACustomGameModeBase::Start()
{
	// player has 100 seconds to defeat all the enemies  starting when the level is loaded
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ACustomGameModeBase::TimerUp, 100, false);
}
// run when the player collides with the EndGamePoint trigger
void ACustomGameModeBase::TriggerLevelChange(FName levelName)
{
	// if the player has killes all the enemies in the scene, take them to the next level
	if (numOfEnemiesKilled >= requiredNumOfKills)
	{
		UGameplayStatics::OpenLevel(GetWorld(), levelName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("tried to leave level, but not enough enemies killed!!"));
	}
}
// when the timer is up, if the player has not killed the required number of enemies, they will be taken to a game over screen
void ACustomGameModeBase::TimerUp()
{
	if (numOfEnemiesKilled < requiredNumOfKills)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
	}
}
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
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ACustomGameModeBase::TimerUp, 100, false);
}
void ACustomGameModeBase::TriggerLevelChange(FName levelName)
{
	if (numOfEnemiesKilled >= requiredNumOfKills)
	{
		UGameplayStatics::OpenLevel(GetWorld(), levelName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("tried to leave level, but not enough enemies killed!!"));
	}
}

void ACustomGameModeBase::TimerUp()
{
	if (numOfEnemiesKilled < requiredNumOfKills)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
	}
}
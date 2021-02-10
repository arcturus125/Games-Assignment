// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"
#include <Kismet/GameplayStatics.h>

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

//UGameplayStatics::OpenLevel(GetWorld(), "WinLevel");
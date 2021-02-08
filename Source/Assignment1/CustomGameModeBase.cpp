// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"
#include <Kismet/GameplayStatics.h>

void ACustomGameModeBase::TriggerLevelChange(FName levelName)
{
	if (allEnemiesKilled)
	{
		UGameplayStatics::OpenLevel(GetWorld(), levelName);
	}
}

//UGameplayStatics::OpenLevel(GetWorld(), "WinLevel");
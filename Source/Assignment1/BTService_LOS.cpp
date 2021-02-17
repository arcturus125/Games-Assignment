// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LOS.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LOS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//if(EnemyAIController->LineOfSightTo(PlayerPawn))

	
	FHitResult Hit;
	FVector thisEnemyLocation = EnemyAIController->GetPawn()->GetActorLocation();
	FVector playerCurrentLocation = PlayerPawn->GetActorLocation();

	auto blackboardRef = EnemyAIController->GetBlackboardComponent();

	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, thisEnemyLocation, playerCurrentLocation, ECC_Visibility);
	if (bDidHit)
	{
		// there is an object obstructing the enemy's LOS of the player
		blackboardRef->ClearValue(TEXT("PlayerPosition"));
	}
	else
	{
		// there is nothing obstructing the enemy's LOS of the player

		blackboardRef->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
		blackboardRef->SetValueAsVector(TEXT("LastKnownPlayerPosition"), PlayerPawn->GetActorLocation());

	}
}
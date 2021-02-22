// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LOS.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LOS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// get a reference to the instance of Ai controller class which is controlling this enemy
	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	// get a reference to the player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	/* NOTE: i could have used GetLineOfSightTo, but since this assignment calls for me to use
	 *  line tracing, i decided to write my own function to check if the enemy has line of sight of the player
	 *  using said line tracing.
	 */
	
	FHitResult Hit; // the details of the collision will be stored in this variable
	// the location i am drawing the raycast from
	FVector thisEnemyLocation = EnemyAIController->GetPawn()->GetActorLocation();
	// the location i am drawing the raycast to
	FVector playerCurrentLocation = PlayerPawn->GetActorLocation();
	// reference the the enemies blackboard so i can change values of the keys
	auto blackboardRef = EnemyAIController->GetBlackboardComponent();

	// the code for the raycast returns a bool if it hits anything
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, thisEnemyLocation, playerCurrentLocation, ECC_Visibility);
	// if the raycast hit an object, then there is something between the player and enemy that is blocking LOS
	if (bDidHit)
	{
		// clears the value of playerposition
		blackboardRef->ClearValue(TEXT("PlayerPosition"));

		/* the blackboard uses this key in a selector node to determine if the enemy has LOS of the player
		 *	clearing this value tells the blackboard that the enemy has lost line of sight 
		 *	and should reflect that in the behaviour tree
		 */
	}
	// if the raycast hits nothing, the enemy will have clear line of sight to the player
	else
	{
		// update the player position to let the blackboard know that LOS of the player has been found
		blackboardRef->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
		// update the enemies last known player position. the enemy will run here and search for the player once LOS is lost
		blackboardRef->SetValueAsVector(TEXT("LastKnownPlayerPosition"), PlayerPawn->GetActorLocation());

	}
}
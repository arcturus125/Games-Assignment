
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"



void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

	// get all gameobjects of type TargetPoint and store them in the Waypoints Array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	
	

	// ##pathfind the enemy to the player
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
	//MoveToActor(PlayerPawn, 10.0f); 

	// move to waypoint 1
	//MoveToActor(Waypoints[0]); 

	//RandomPatrol();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
	//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

	for (AActor* Waypoint : Waypoints)
	{
		if (Waypoint->ActorHasTag(TEXT("Lookout")))
		{
			lookoutPoint = Waypoint;

			GetBlackboardComponent()->SetValueAsVector(TEXT("LookoutPosition"), lookoutPoint->GetActorLocation());
		}
		if (Waypoint->ActorHasTag(TEXT("Home")))
		{
			lookoutPoint = Waypoint;

			GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), lookoutPoint->GetActorLocation());
		}
	}

}
void AEnemyAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	LOScheck();
}

AActor* AEnemyAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void AEnemyAIController::RandomPatrol()
{

	MoveToActor(ChooseWaypoint()); 
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const
	FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//RandomPatrol();
}
void AEnemyAIController::LOScheck()
{
	// moved to BTService _ LOS
	FHitResult Hit;
	FVector thisEnemyLocation = GetPawn()->GetActorLocation();
	FVector playerCurrentLocation = PlayerPawn->GetActorLocation();

	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, thisEnemyLocation, playerCurrentLocation, ECC_Visibility);
	if (bDidHit)
	{
		// there is an object obstructing the enemy's LOS of the player
		GetBlackboardComponent()->ClearValue(TEXT("PlayerPosition"));
	}
	else
	{
		// there is nothing obstructing the enemy's LOS of the player

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerPosition"), PlayerPawn->GetActorLocation());

	}
}
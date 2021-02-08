
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
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

	for (AActor* Waypoint : Waypoints)
	{
		if (Waypoint->ActorHasTag(TEXT("Lookout")))
		{
			lookoutPoint = Waypoint;

			GetBlackboardComponent()->SetValueAsVector(TEXT("LookoutPosition"), lookoutPoint->GetActorLocation());
		}
	}

}
void AEnemyAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
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

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"



void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}
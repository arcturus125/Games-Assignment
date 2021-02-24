
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"



void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

	
}
void AEnemyAIController::StartTree()
{
	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no behaviour tree added"));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGamePoint.h"
#include <Components/BoxComponent.h>
#include "CustomGameModeBase.h"

// Sets default values
AEndGamePoint::AEndGamePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// create the hitbox used as a trigger
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision zone"));
	SetRootComponent(collider);

	// runs the beginOverlap function when the trigger detects a collision
	collider->OnComponentBeginOverlap.AddDynamic(this, &AEndGamePoint::BeginOverlap);

}
void AEndGamePoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision"));
	// check the player is the actor causing the trigger event
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		gamemode->TriggerLevelChange(nextLevelName, killsNeededOnNextLevel);
	}
}
// Called when the game starts or when spawned
void AEndGamePoint::BeginPlay()
{
	Super::BeginPlay();

	gamemode = Cast<ACustomGameModeBase>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void AEndGamePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


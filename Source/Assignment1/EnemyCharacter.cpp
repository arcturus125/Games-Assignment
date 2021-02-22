// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include <Assignment1\Bullet.h>
#include <Assignment1\CustomGameModeBase.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(RootComponent);
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// reduce the enemies health
	Health -= DamageAmount;
	// if the enemy's health is negative, increase the score and delete the enemy
	if (Health <= 0)
	{
		auto gamemode = Cast<ACustomGameModeBase>(GetWorld()->GetAuthGameMode());
		gamemode->numOfEnemiesKilled++;
		this->Destroy();
	}
	return 0.0f;
}


// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(GetController());
	enemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("LookoutPosition"), lookoutPoint->GetActorLocation());
	enemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), homePoint->GetActorLocation());

}


void AEnemyCharacter::ShootPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector SpawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerPawn->GetActorLocation());
	ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(bulletClass, SpawnLocation, SpawnRotation);
	TempBullet->SetOwner(this);
	TempBullet->PlayShootSound();
	
}
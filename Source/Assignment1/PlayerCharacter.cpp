// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"// import the camera
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/Pawn.h"
#include "CustomMovementComponent.h"
#include "Bullet.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	springArm->SetupAttachment(RootComponent);
	springArm->bEnableCameraLag = true; // when you move, the camera doesnt move immedately (lerp)

	// ### NOTE: instead of setting these in code, i am setting them in the blueprint
	//springArm->SetRelativeRotation((new FRotator(320.0f, 0.0f, 0.0f))->Quaternion()); // change the angle the springarm looks at the object
	//springArm->TargetArmLength = 600.0f; // the camera Z offset

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera"); // create a camera
	Camera->SetupAttachment(springArm); // attach the camera to the springarm

	PawnMovement = CreateDefaultSubobject<UCustomMovementComponent>(TEXT("Pawn Movement"));

	// position of spawn point is assigned in blueprint
	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(springArm);

	
}
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// reduce the players health
	UE_LOG(LogTemp, Warning, TEXT("Player damaged!!"));
	Health -= DamageAmount;
	if (Health <= 0)
	{
		// if the player's health is negative, take them to the game over screen
		UE_LOG(LogTemp, Warning, TEXT("Player Dead!!"));
		UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
	}
	return 0.0f;
}

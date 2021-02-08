// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"// import the camera
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/Pawn.h"
#include "CustomMovementComponent.h"


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
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(springArm);

}












// following lab sheet, says to delete these

//// Called when the game starts or when spawned
//void APlayerCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void APlayerCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//
//}
//
// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	bulletMesh->SetupAttachment(RootComponent);
	// dont want bullet to be affected by gravity
	bulletMesh->SetSimulatePhysics(false);
	bulletMesh->SetEnableGravity(false);


	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectile"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	projectileMovement->ProjectileGravityScale = 0;
	InitialLifeSpan = 10.0f;




}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


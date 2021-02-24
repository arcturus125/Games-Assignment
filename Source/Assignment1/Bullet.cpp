// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Assignment1\EnemyCharacter.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add the mesh to the bluprint and set the mesh to the root component
	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	bulletMesh->SetupAttachment(RootComponent);

	// make this mesh a projectile ans set its speed and lifespan
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectile"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;


	// dont want bullet to be affected by gravity
	bulletMesh->SetSimulatePhysics(true);
	bulletMesh->SetEnableGravity(false);
	projectileMovement->ProjectileGravityScale = 0;

	//// collision stuffs
	bulletMesh->SetNotifyRigidBodyCollision(true); // tell the mesh to listen for collisions
	bulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnCompHit); // run OnCompHit() when the bullet hits something
	

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


//function called when a player or enemy shoots a bullet,
// plays a sound at the position of the bullet's spawn point
void ABullet::PlayShootSound()
{
	// play sound when enemy is hit
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		shootSound,
		GetActorLocation(),
		1.0f,
		1.0f,
		0.0f
	);
}


// runs when the bullet hits another object in the scene
void ABullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr) // error catching
	{
		// check if the bullet hit an enemy
		if(OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet HIT Enemy!!"));

			AActor* ProjectileOwner = GetOwner();
			// damage the enemy
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				bulletDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

			// play sound when enemy is hit
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				deathSound,
				GetActorLocation(),
				1.0f,
				1.0f,
				0.0f
			);

			// once bullet has hit, delete the actor from the scene so there isnt a floating bullet
			this->Destroy();
		}
		// if a bullet hit the player
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet HIT Player!!"));

			AActor* ProjectileOwner = GetOwner();
			// damage the player
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				bulletDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

			// play sound when enemy is hit
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				deathSound,
				GetActorLocation(),
				1.0f,
				1.0f,
				0.0f
			);


			// once bullet has hit, delete the actor from the scene so there isnt a floating bullet
			this->Destroy();
		}
		// if the bullet has hit a disctructable object
		else if (OtherActor->ActorHasTag(TEXT("Distructable")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet HIT distructable!!"));
			AActor* ProjectileOwner = GetOwner();
			// damage the enemy
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				bulletDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);
		}
		else if (OtherActor->ActorHasTag(TEXT("Impulse")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet HIT impulse!!"));
			AActor* ProjectileOwner = GetOwner();

			UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			float ImpulseForce = 500;
			rootComp->AddImpulse(GetActorForwardVector() * ImpulseForce);
		}
	}
}
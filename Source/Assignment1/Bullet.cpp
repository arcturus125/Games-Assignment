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

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	bulletMesh->SetupAttachment(RootComponent);


	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectile"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;


	// dont want bullet to be affected by gravity
	bulletMesh->SetSimulatePhysics(false);
	bulletMesh->SetEnableGravity(false);
	projectileMovement->ProjectileGravityScale = 0;

	// tell the billet to listen for collisions
	//bulletMesh->SetNotifyRigidBodyCollision(true);

	//// collision stuffs
	//collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	bulletMesh->SetNotifyRigidBodyCollision(true);
	//collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::BeginOverlap);
	bulletMesh->SetSimulatePhysics(true);
	//collider->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	bulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnCompHit);

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


void ABullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Bullet Hit An Object"));


	if (OtherActor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Object not null"));
		//if (OtherActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass()))
		if(OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet HIT!!"));

			AActor* ProjectileOwner = GetOwner();
			// damage the enemy
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				bulletDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

			// once bullet has hit, delete the actor from the scene so there isnt a floating bullet
			this->Destroy();
		}
	}
}
//
//
//
//void ABullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
//	AActor* OtherActor,
//	UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex,
//	bool bFromSweep,
//	const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Bullet Hit Something"));
//
//	//if (OtherActor->GetClass()->IsChildOf(ABullet::StaticClass()))
//	//{
//	//	UE_LOG(LogTemp, Warning, TEXT("Bullet HIT!!"));
//
//	//	AActor* ProjectileOwner = GetOwner();
//	//	// damage the enemy
//	//	UGameplayStatics::ApplyDamage(
//	//		OtherActor, //actor that will be damaged
//	//		bulletDamage, //the base damage to apply
//	//		ProjectileOwner->GetInstigatorController(), //controller that caused the damage
//	//		this, //Actor that actually caused the damage
//	//		UDamageType::StaticClass() //class that describes the damage that was done
//	//	);
//
//	//	// once bullet has hit, delete the actor from the scene so there isnt a floating bullet
//	//	OtherComp->DestroyComponent();
//	//}
//}
// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleTarget.h"
#include "DemoShooter/Actors/ObjectSpawner.h"
#include "DemoShooter/PlayerControllers/ShooterPlayerController.h"

// Sets default values
ABottleTarget::ABottleTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle mesh"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ABottleTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABottleTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABottleTarget::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.GetTypeID() == FPointDamageEvent::ClassID)
	{
		const FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)&DamageEvent;
		MeshComponent->AddImpulse(PointDamageEvent->ShotDirection);
	}

	AObjectSpawner* Spawner = Cast<AObjectSpawner>(GetOwner());
	if (Spawner != nullptr)
	{
		Spawner->CheckRespawn();
	}

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(EventInstigator);
	if (PlayerController != nullptr)
	{
		PlayerController->AddPoints(Points);
	}

	return DamageAmount;
}


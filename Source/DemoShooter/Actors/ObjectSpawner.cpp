// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "Components/SphereComponent.h"
#include "DemoShooter/Actors/BottleTarget.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	SphereCollision->SetRelativeLocation(GetActorLocation());
	SphereCollision->SetSphereRadius(12);
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	BottleSpawned = GetWorld()->SpawnActor<ABottleTarget>(BottleTargetClass, RootComponent->GetComponentTransform());

	GetWorld()->GetTimerManager().SetTimer(RespawnHandle, this, &AObjectSpawner::CheckRespawn, 2.0f, true);

	/*
	
		TODO: When I hitted the bottle and after 2 seconds destroy it (or break it and destroy) 
			then call the timer and respawn after 2 seconds or so
	
	*/
}

// Called every frame
void AObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectSpawner::CheckRespawn()
{
	if (!SphereCollision->IsOverlappingActor(BottleSpawned))
	{
		BottleSpawned->Destroy();

		BottleSpawned = GetWorld()->SpawnActor<ABottleTarget>(BottleTargetClass, RootComponent->GetComponentTransform());
	}
}


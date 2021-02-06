// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "DemoShooter/Actors/BottleTarget.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TSubclassOf<ABottleTarget> BottleTargetClass = BottleTargetClasses[FMath::RandRange(0, BottleTargetClasses.Num() - 1)];
	BottleSpawned = GetWorld()->SpawnActor<ABottleTarget>(BottleTargetClass, RootComponent->GetComponentTransform());
	BottleSpawned->SetOwner(this);
}

// Called every frame
void AObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectSpawner::CheckRespawn()
{
	if (GetWorld()->GetTimerManager().TimerExists(RespawnHandle))
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(RespawnHandle, this, &AObjectSpawner::Respawn, RespawnTime, false);
}

void AObjectSpawner::Respawn()
{
	BottleSpawned->Destroy();
	
	TSubclassOf<ABottleTarget> BottleTargetClass = BottleTargetClasses[FMath::RandRange(0, BottleTargetClasses.Num() - 1)];
	BottleSpawned = GetWorld()->SpawnActor<ABottleTarget>(BottleTargetClass, RootComponent->GetComponentTransform());
	BottleSpawned->SetOwner(this);
}


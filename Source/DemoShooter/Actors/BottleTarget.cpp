// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleTarget.h"

// Sets default values
ABottleTarget::ABottleTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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


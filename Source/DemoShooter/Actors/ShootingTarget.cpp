// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingTarget.h"
#include "Components/SphereComponent.h"

// Sets default values
AShootingTarget::AShootingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	SphereCollision->SetupAttachment(Root);

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingTarget"));
	TargetMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AShootingTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


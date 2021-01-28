// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCounter.h"
#include "DemoShooter/Actors/GunBase.h"
#include "Components/SphereComponent.h"


// Sets default values
AWeaponCounter::AWeaponCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Counter"));
	RootComponent = StaticMesh;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	SkeletalMesh->SetupAttachment(StaticMesh);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(SkeletalMesh);
	SphereCollision->SetSphereRadius(75.0f);
}

// Called when the game starts or when spawned
void AWeaponCounter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AGunBase> AWeaponCounter::GetGunClass() const
{
	return GunClass;
}


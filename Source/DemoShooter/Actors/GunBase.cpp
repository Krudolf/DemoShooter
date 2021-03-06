// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "DemoShooter/Actors/BulletBase.h"

#define OUT

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal mesh"));
	SkeletalMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleEmitter, SkeletalMesh, TEXT("SK_Wep_Muzzle"));

	FVector ShootDirection;
	FHitResult Hit;
	bool bSuccess = BulletTrace(OUT Hit, OUT ShootDirection);
	if (bSuccess)
	{
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, false, 2);
		
		const FVector SpawnLocation = SkeletalMesh->GetSocketLocation(TEXT("SK_Wep_Muzzle"));
		FRotator HitRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, Hit.Location);

		ABulletBase* Bullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass, SpawnLocation, HitRotation);
		Bullet->SetOwner(this);
		Bullet->SetBulletVelocity(HitRotation.Vector());
		Bullet->setDamage(Damage);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEmitter, Hit.Location, ShootDirection.Rotation());
	}
}

bool AGunBase::BulletTrace(FHitResult& Hit, FVector& ShootDirection)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not OwnerPawn detected"));
		return false;
	}

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not OwnerController detected"));
		return false;
	}

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	ShootDirection = -ViewPointRotation.Vector();

	FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * ShootMaxRange;

	//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90, 2, FColor::Red, true);
	//DrawDebugLine(GetWorld(), ViewPointLocation, EndLocation, FColor::Red, true, 2);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OUT Hit, ViewPointLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);
}

void AGunBase::SetContinueShooting(bool bContinueShooting)
{
	if (bContinueShooting)
	{
		GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &AGunBase::PullTrigger, FireRate, true, 0);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FireRateTimer);
	}
}


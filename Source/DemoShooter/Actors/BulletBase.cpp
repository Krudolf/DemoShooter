// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet mesh"));
	RootComponent = BulletMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = BulletSpeed;
	ProjectileMovement->MaxSpeed = BulletSpeed;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();

	BulletMesh->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::SetBulletVelocity(FVector InForwardVector)
{
	ForwardVector = InForwardVector;
	ProjectileMovement->Velocity = ForwardVector * BulletSpeed;
}

void ABulletBase::setDamage(float InDamage)
{
	Damage = InDamage;
}

void ABulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FPointDamageEvent DamageEvent(Damage, Hit, ForwardVector, nullptr);
	OtherActor->TakeDamage(Damage, DamageEvent, GetOwner()->GetInstigatorController(), this);

	Destroy();
}


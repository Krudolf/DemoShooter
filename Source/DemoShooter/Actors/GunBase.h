// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class DEMOSHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleEmitter;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEmitter;

	UPROPERTY(EditAnywhere)
	float ShootMaxRange = 1000.0f;

	bool BulletTrace(FHitResult& Hit, FVector& ShootDirection);

};

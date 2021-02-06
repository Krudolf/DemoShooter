// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "ObjectSpawner.generated.h"

class ABottleTarget;
class USphereComponent;

UCLASS()
class DEMOSHOOTER_API AObjectSpawner : public ATargetPoint
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABottleTarget> BottleTargetClass;

	ABottleTarget* BottleSpawned;

	FTimerHandle RespawnHandle;

	// FUNCTIONS
	void CheckRespawn();

};

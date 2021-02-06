// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "ObjectSpawner.generated.h"

class ABottleTarget;

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


	void CheckRespawn();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABottleTarget> BottleTargetClass;

	UPROPERTY(EditAnywhere)
	float RespawnTime = 2.0f;

	ABottleTarget* BottleSpawned;

	FTimerHandle RespawnHandle;

	// FUNCTIONS
	void Respawn();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartSpawners();

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle BottleGameHandler;

private:
	TArray<AActor*> FoundTextRender;
	TArray<AActor*> FoundSpawners;

	UPROPERTY(EditAnywhere)
	float GameTime = 15.0f;


	void EndGame();
};

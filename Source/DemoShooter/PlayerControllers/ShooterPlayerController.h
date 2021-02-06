// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AddPoints(int32 PointsToAdd);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentPoints();

	void CreatePointsWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PointsClass;

	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	int32 CurrentPoints = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}

	CreatePointsWidget();
}

void AShooterPlayerController::AddPoints(int32 PointsToAdd)
{
	CurrentPoints += PointsToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Points %i"), CurrentPoints);
}

int32 AShooterPlayerController::GetCurrentPoints()
{
	return CurrentPoints;
}

void AShooterPlayerController::CreatePointsWidget()
{
	UUserWidget* PointsWidget = CreateWidget(this, PointsClass);
	if (PointsWidget != nullptr)
	{
		PointsWidget->AddToViewport();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DemoShooter/GameModes/ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"


void AShooterPlayerController::BeginPlay()
{
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}

	CreatePointsWidget();
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Start"), IE_Pressed, this, &AShooterPlayerController::StartSpawners);
}

void AShooterPlayerController::StartSpawners()
{
	CurrentPoints = 0;

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AShooterGameMode* ShooterGameMode = Cast<AShooterGameMode>(GameModeBase);
	
	if(ShooterGameMode == nullptr)
	{
		return;
	}

	ShooterGameMode->StartSpawners();
}

void AShooterPlayerController::AddPoints(int32 PointsToAdd)
{
	CurrentPoints += PointsToAdd;
}

int32 AShooterPlayerController::GetCurrentPoints()
{
	return CurrentPoints;
}

int32 AShooterPlayerController::GetMaxPoints()
{
	return MaxPoints;
}

void AShooterPlayerController::CreatePointsWidget()
{
	UUserWidget* PointsWidget = CreateWidget(this, PointsClass);
	if (PointsWidget != nullptr)
	{
		PointsWidget->AddToViewport();
	}
}

void AShooterPlayerController::CheckMaxPoints()
{
	if (CurrentPoints > MaxPoints)
	{
		MaxPoints = CurrentPoints;
	}
}
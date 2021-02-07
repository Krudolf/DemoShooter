// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DemoShooter/Actors/ObjectSpawner.h"
#include "Engine/TextRenderActor.h"
#include "DemoShooter/PlayerControllers/ShooterPlayerController.h"

#define OUT

void AShooterGameMode::StartSpawners()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextRenderActor::StaticClass(), OUT FoundTextRender);
	for (AActor* ActorText : FoundTextRender)
	{
		ATextRenderActor* TextRender = Cast<ATextRenderActor>(ActorText);
		TextRender->SetActorHiddenInGame(true);
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectSpawner::StaticClass(), OUT FoundSpawners);
	for (AActor* ActorSpawner : FoundSpawners)
	{
		AObjectSpawner* Spawner = Cast<AObjectSpawner>(ActorSpawner);
		if (Spawner != nullptr)
		{
			Spawner->CheckRespawn();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(BottleGameHandler, this, &AShooterGameMode::EndGame, GameTime, false);
}

void AShooterGameMode::EndGame()
{
	for (AActor* ActorText : FoundTextRender)
	{
		ATextRenderActor* TextRender = Cast<ATextRenderActor>(ActorText);
		TextRender->SetActorHiddenInGame(false);
	}

	for (AActor* ActorSpawner : FoundSpawners)
	{
		AObjectSpawner* Spawner = Cast<AObjectSpawner>(ActorSpawner);
		if (Spawner != nullptr)
		{
			Spawner->ClearAndDestroy();
		}
	}

	AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (ShooterPlayerController != nullptr)
	{
		ShooterPlayerController->CheckMaxPoints();
	}
}

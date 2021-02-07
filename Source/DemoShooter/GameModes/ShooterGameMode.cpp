// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DemoShooter/Actors/ObjectSpawner.h"
#include "Engine/TextRenderActor.h"

#define OUT

void AShooterGameMode::StartSpawners()
{
	TArray<AActor*> FoundTextRender;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextRenderActor::StaticClass(), OUT FoundTextRender);
	for (AActor* ActorText : FoundTextRender)
	{
		ATextRenderActor* TextRender = Cast<ATextRenderActor>(ActorText);
		TextRender->SetActorHiddenInGame(true);
	}


	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectSpawner::StaticClass(), OUT FoundSpawners);

	for (AActor* ActorSpawner : FoundSpawners)
	{
		AObjectSpawner* Spawner = Cast<AObjectSpawner>(ActorSpawner);
		if (Spawner != nullptr)
		{
			Spawner->CheckRespawn();
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DemoShooter/Actors/GunBase.h"
#include "DrawDebugHelpers.h"
#include "DemoShooter/Actors/WeaponCounter.h"

#define OUT

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GunClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ShooterCharacter has not a GunClass selected"));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::StartShooting);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AShooterCharacter::StopShooting);
	PlayerInputComponent->BindAction(TEXT("Pick"), IE_Pressed, this, &AShooterCharacter::PickItem);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::StartShooting()
{
	Gun->SetContinueShooting(true);
}

void AShooterCharacter::StopShooting()
{
	Gun->SetContinueShooting(false);
}

void AShooterCharacter::PickItem()
{
	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(OUT Location, OUT Rotation);
	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 1, FColor::Red, false, 2);

	FVector End = Location + Rotation.Vector() * PickUpRange;
	//DrawDebugLine(GetWorld(), Location, End, FColor::Red, false, 2);

	FHitResult Hit;
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	bool bSuccess = GetWorld()->LineTraceSingleByObjectType(OUT Hit, Location, End, QueryParams);
	if (bSuccess)
	{
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, false, 2);
		
		AWeaponCounter* WeaponCounter = Cast<AWeaponCounter>(Hit.GetActor());
		if (WeaponCounter != nullptr)
		{
			if (Gun->Destroy())
			{
				Gun = GetWorld()->SpawnActor<AGunBase>(WeaponCounter->GetGunClass());
				Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
				Gun->SetOwner(this);
			}
		}
	}
}

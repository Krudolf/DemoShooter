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

	WeaponInventory.Push(nullptr);
	WeaponInventory.Push(nullptr);

	/*Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);*/
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
	PlayerInputComponent->BindAxis(TEXT("ChangeWeapon"), this, &AShooterCharacter::ChangeWeapon);
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
	if (ActiveGun != nullptr)
	{
		ActiveGun->SetContinueShooting(true);
	}
}

void AShooterCharacter::StopShooting()
{
	if (ActiveGun != nullptr)
	{
		ActiveGun->SetContinueShooting(false);
	}
}

void AShooterCharacter::ChangeWeapon(float AxisValue)
{
	int32 OldWeaponIndex = ActiveWeaponIndex;
	ActiveWeaponIndex = FMath::Clamp(ActiveWeaponIndex + (int32)AxisValue, 0, 1);

	if (OldWeaponIndex == ActiveWeaponIndex)
	{
		return;
	}

	ActiveGun = WeaponInventory[ActiveWeaponIndex];

	if (WeaponInventory[OldWeaponIndex] != nullptr)
	{
		WeaponInventory[OldWeaponIndex]->SetActorHiddenInGame(true);
	}

	if (WeaponInventory[ActiveWeaponIndex] != nullptr)
	{
		WeaponInventory[ActiveWeaponIndex]->SetActorHiddenInGame(false);
	}
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
			CreateGun(WeaponCounter->GetGunClass());
		}
	}
}

void AShooterCharacter::CreateGun(TSubclassOf<AGunBase> NewGunClass)
{
	if (WeaponInventory[0] == nullptr)
	{
		ActiveWeaponIndex = 0;
	}
	else if (WeaponInventory[1] == nullptr)
	{
		WeaponInventory[0]->SetActorHiddenInGame(true);
		ActiveWeaponIndex = 1;
	}
	else
	{
		WeaponInventory[ActiveWeaponIndex]->Destroy();
	}
	WeaponInventory[ActiveWeaponIndex] = GetWorld()->SpawnActor<AGunBase>(NewGunClass);
	WeaponInventory[ActiveWeaponIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	WeaponInventory[ActiveWeaponIndex]->SetOwner(this);
	ActiveGun = WeaponInventory[ActiveWeaponIndex];
}

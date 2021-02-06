// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGunBase;

UCLASS()
class DEMOSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// FUNTIONS
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartShooting();
	void StopShooting();
	void ChangeWeapon(float AxisValue);

	void PickItem();
	void CreateGun(TSubclassOf<AGunBase> GunClass);


	// VARIABLES
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunBase> GunClass;

	UPROPERTY()
	AGunBase* ActiveGun = nullptr;

	TArray<AGunBase*> WeaponInventory;

	int32 ActiveWeaponIndex = 0;

	UPROPERTY(EditAnywhere)
	float PickUpRange = 400.0f;
};

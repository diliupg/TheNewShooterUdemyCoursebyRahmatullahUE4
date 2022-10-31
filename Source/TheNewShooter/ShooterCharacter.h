// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

//class AGunActor; // forward declare

UCLASS()
class THENEWSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
 
	class AGunActor* GunSpawn;

	// Axis Map Functions
	void MoveForward( float MoveValue );
	void MoveRight( float MoveValue );
	void LookUp( float MoveValue );
	void LookSides( float MoveValue );

	UPROPERTY(EditAnywhere )
	TSubclassOf<AGunActor> GunBPClass;

	void PlayerShoot( );
};

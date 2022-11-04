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

	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser ) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintPure ) // this will be called in the Blueprint
	bool IsDead( ) const;

	void Shoot( );

private:
 
	class AGunActor* SpawnedGun;

	// Axis Map Functions
	void MoveForward( float MoveValue );
	void MoveRight( float MoveValue );
	void LookUp( float MoveValue );
	void LookSides( float MoveValue );

	UPROPERTY(EditAnywhere )
	TSubclassOf<AGunActor> GunBPClass;

	float MaxHealth;

	float CurrentHealth;
};

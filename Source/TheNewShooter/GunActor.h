// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class THENEWSHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditAnywhere )
	class USkeletalMeshComponent* Gun;

	UPROPERTY(EditAnywhere )
	class UParticleSystem* GunFireEffect;

	UPROPERTY( EditAnywhere )
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere )
	class USoundBase* GunFireSound;

	UPROPERTY( EditAnywhere )
	class USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly )
	float EndLocationDistance;

	UPROPERTY( EditDefaultsOnly )
	float DamageAmount;

public:

	void GunShoot( );

};

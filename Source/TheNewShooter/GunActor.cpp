// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundCue.h"

// Sets default values
AGunActor::AGunActor() :
	EndLocationDistance(5000.f ),
	DamageAmount(35.f )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "Gun" ) );

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame 
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::GunShoot( )
{
	UGameplayStatics::SpawnSound2D( GetWorld(), MachineGunFire);
	UGameplayStatics::SpawnEmitterAttached( GunFireEffect, Gun, TEXT( "MuzzleFlash" ) );

	APawn* OwnerPawn = Cast<APawn>( GetOwner( ) );
	if ( OwnerPawn == nullptr ) { return; }

	AController* OwnerController = OwnerPawn->GetController( );
	if ( OwnerPawn == nullptr ) { return; }

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint( Location, Rotation );

	FVector EndLocation = Location + Rotation.Vector( ) * EndLocationDistance;

	FHitResult Hit;
	bool bDone = GetWorld( )->LineTraceSingleByChannel( Hit, Location, EndLocation, ECollisionChannel::ECC_GameTraceChannel1 );

	if ( bDone )
	{
		FVector ShotDirection = -Rotation.Vector( );
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld( ), ImpactEffect, Hit.Location, ShotDirection.Rotation( ) );

		FPointDamageEvent DamageEvent( DamageAmount, Hit, ShotDirection, nullptr );

		AActor* HitActor = Hit.GetActor( );
		if ( HitActor != nullptr )
		{
			HitActor->TakeDamage( DamageAmount, DamageEvent, OwnerController, this );
		}
	}
}


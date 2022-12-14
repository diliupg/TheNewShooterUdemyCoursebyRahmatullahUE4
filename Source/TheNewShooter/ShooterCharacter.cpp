// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "TheNewShooterGameModeBase.h"



// Sets default values
AShooterCharacter::AShooterCharacter() :
	MaxHealth(100.f ),
	CurrentHealth(MaxHealth ),
	MaxAngle( -45.f ),
	MinAngle( 45.f )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	

	CurrentHealth = MaxHealth;

	GunSpawn = GetWorld( )->SpawnActor<AGunActor>( GunBPClass );
	GunSpawn->AttachToComponent( GetMesh( ), FAttachmentTransformRules::KeepRelativeTransform, TEXT( "GunSocket_r" ) );

	GunSpawn->SetOwner( this );

	//Set the Camera Pitch 
	ShooterPlayerController = Cast<APlayerController>( Controller );

	if ( ShooterPlayerController )
	{
		if ( ShooterPlayerController->PlayerCameraManager )
		{
			ShooterPlayerController->PlayerCameraManager->ViewPitchMin = MaxAngle; // Use whatever values you want
			ShooterPlayerController->PlayerCameraManager->ViewPitchMax = MinAngle;
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( CurrentHealth <= 0 && !DestroyTimerSet )
	{
		DestroyTimerSet = true;

		GetWorld( )->GetTimerManager( ).SetTimer( DeathTimer, this, &AShooterCharacter::OnTimerEndDestroy, 2.f, false );
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld( ), DeathEffect, GetTransform( ) );
	}

}

float AShooterCharacter::TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser )
{
	float AppliedDamage = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator, DamageCauser );
	AppliedDamage = FMath::Min( CurrentHealth, AppliedDamage );

	CurrentHealth -= AppliedDamage;
	//UE_LOG( LogTemp, Warning, TEXT( "Health : %f" ), CurrentHealth );

	if ( IsDead( ) )
	{
		ATheNewShooterGameModeBase* GameMode = GetWorld( )->GetAuthGameMode<ATheNewShooterGameModeBase>( );

		if ( GameMode != nullptr )
		{
			GameMode->PawnKilled( this );
		}
		
	}
	return AppliedDamage;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Axis control
	PlayerInputComponent->BindAxis( TEXT( "MoveForward" ), this, &AShooterCharacter::MoveForward );
	PlayerInputComponent->BindAxis( TEXT( "MoveRight" ), this, &AShooterCharacter::MoveRight );
	PlayerInputComponent->BindAxis( TEXT( "Lookup" ), this, &AShooterCharacter::LookUp );
	PlayerInputComponent->BindAxis( TEXT( "LookSides" ), this, &AShooterCharacter::LookSides );

	//Bind Action control
	PlayerInputComponent->BindAction( TEXT( "Jump" ), EInputEvent::IE_Pressed, this, &ACharacter::Jump );
	PlayerInputComponent->BindAction( TEXT( "Shoot" ), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShootGun );
}

void AShooterCharacter::MoveForward( float MoveValue )
{
	AddMovementInput( GetActorForwardVector( ), MoveValue, IsMoveInputIgnored( ) );
}

void AShooterCharacter::MoveRight( float MoveValue )
{
	AddMovementInput( GetActorRightVector( ), MoveValue, IsMoveInputIgnored( ) );
}

void AShooterCharacter::LookUp( float MoveValue )
{
	AddControllerPitchInput( MoveValue );
}

void AShooterCharacter::LookSides( float MoveValue )
{
	AddControllerYawInput( MoveValue );
}


bool AShooterCharacter::IsDead( ) const
{
	//if ( CurrentHealth <= 0 ) { UE_LOG( LogTemp, Warning, TEXT( "Health Just Got Over!!!" ) ); }
	
	return CurrentHealth <= 0;
}


void AShooterCharacter::OnTimerEndDestroy( )
{
	Destroy( );
	GunSpawn->Destroy();
	//UE_LOG( LogTemp, Warning, TEXT( "Enemy Object Destroyed!!!" ) );
}

void AShooterCharacter::ShootGun( )
{
	GunSpawn->GunShoot( );
	//UE_LOG( LogTemp, Warning, TEXT( "Fired!`" ) );
}

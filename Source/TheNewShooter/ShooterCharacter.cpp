// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Math/UnrealMathUtility.h"
#include "TheNewShooterGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	MaxHealth(100.f ),
	CurrentHealth(MaxHealth ),
	MaxAngle(45.f ),
	MinAngle(-45.f ),
	CameraFOVZoom(45.f ),
	CameraFOVDefault(90.f )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	SpawnedGun = GetWorld( )->SpawnActor<AGunActor>( GunBPClass );
	SpawnedGun->AttachToComponent( GetMesh( ), FAttachmentTransformRules::KeepRelativeTransform, TEXT( "GunSocket_r" ) );

	SpawnedGun->SetOwner( this );

	//Set the Camera Pitch 
	ShooterPlayerController = Cast<APlayerController>( Controller );

	Player = GetCharacterMovement( );

	if ( ShooterPlayerController )
	{
		if ( ShooterPlayerController->PlayerCameraManager )
		{
			ShooterPlayerController->PlayerCameraManager->ViewPitchMin = -MaxAngle; // Use whatever values you want
			ShooterPlayerController->PlayerCameraManager->ViewPitchMax = MinAngle;
		}
	}

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( IsDead() )
	{
		Destroy( );
		SpawnedGun->Destroy( );
	}

}

float AShooterCharacter::TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser )
{
	float AppliedDamage = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator, DamageCauser );
	AppliedDamage = FMath::Min( CurrentHealth, AppliedDamage );

	CurrentHealth -= AppliedDamage;
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
	PlayerInputComponent->BindAction( TEXT( "Shoot" ), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot );
	PlayerInputComponent->BindAction( TEXT( "CameraZoom" ), EInputEvent::IE_Pressed, this, &AShooterCharacter::ZoomIn );
	PlayerInputComponent->BindAction( TEXT( "CameraZoom" ), EInputEvent::IE_Released, this, &AShooterCharacter::ZoomOut );
	PlayerInputComponent->BindAction( TEXT( "Walk_Run" ), EInputEvent::IE_Pressed, this, &AShooterCharacter::Run );
	PlayerInputComponent->BindAction( TEXT( "Walk_Run" ), EInputEvent::IE_Released, this, &AShooterCharacter::Walk );
}

void AShooterCharacter::MoveForward( float MoveValue )
{
	//UE_LOG( LogTemp, Warning, TEXT( "Move Forward-Backward: %f" ), MoveValue );
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


void AShooterCharacter::ZoomIn( )
{
	ShooterPlayerController->PlayerCameraManager->SetFOV( CameraFOVZoom );
}


void AShooterCharacter::ZoomOut( )
{
	ShooterPlayerController->PlayerCameraManager->SetFOV( CameraFOVDefault );
}


void AShooterCharacter::Walk( )
{
	Player->MaxWalkSpeed = 300.f;
}


void AShooterCharacter::Run( )
{
	Player->MaxWalkSpeed = 600.f;
}

bool AShooterCharacter::IsDead( ) const
{
	return CurrentHealth <= 0; 
}


float AShooterCharacter::HealthPercentage( ) const
{
	return CurrentHealth / MaxHealth; 
}

void AShooterCharacter::Shoot( )
{
	SpawnedGun->GunShoot( );
}

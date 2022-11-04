// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	MaxHealth(100.f ),
	CurrentHealth(MaxHealth )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AShooterCharacter::TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser )
{
	float AppliedDamage = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator, DamageCauser );
	AppliedDamage = FMath::Min( CurrentHealth, AppliedDamage );

	CurrentHealth -= AppliedDamage;
	UE_LOG( LogTemp, Warning, TEXT( "Health : %f, " ", %f" ), CurrentHealth, AppliedDamage );

	return 0;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	SpawnedGun = GetWorld( )->SpawnActor<AGunActor>( GunBPClass );
	SpawnedGun->AttachToComponent( GetMesh( ), FAttachmentTransformRules::KeepRelativeTransform, TEXT( "GunSocket_r" ) );

	SpawnedGun->SetOwner( this );

	APlayerController* ShooterPlayerController = Cast<APlayerController>( Controller );
	if ( ShooterPlayerController )
	{
		if ( ShooterPlayerController->PlayerCameraManager )
		{
			ShooterPlayerController->PlayerCameraManager->ViewPitchMin = -45.0; // Use whatever values you want
			ShooterPlayerController->PlayerCameraManager->ViewPitchMax = 45.0;
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

bool AShooterCharacter::IsDead( ) const
{
	return CurrentHealth <= 0; 
}

void AShooterCharacter::Shoot( )
{
	SpawnedGun->GunShoot( );
}

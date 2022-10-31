// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"

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
	
	GunSpawn = GetWorld( )->SpawnActor<AGunActor>( GunBPClass );
	GunSpawn->AttachToComponent( GetMesh( ), FAttachmentTransformRules::KeepRelativeTransform, TEXT( "GunSocket_r" ) );

	GunSpawn->SetOwner( this );
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

	//Bind Axis control
	PlayerInputComponent->BindAxis( TEXT( "MoveForward" ), this, &AShooterCharacter::MoveForward );
	PlayerInputComponent->BindAxis( TEXT( "MoveRight" ), this, &AShooterCharacter::MoveRight );
	PlayerInputComponent->BindAxis( TEXT( "Lookup" ), this, &AShooterCharacter::LookUp );
	PlayerInputComponent->BindAxis( TEXT( "LookSides" ), this, &AShooterCharacter::LookSides );

	//Bind Action control
	PlayerInputComponent->BindAction( TEXT( "Jump" ), EInputEvent::IE_Pressed, this, &ACharacter::Jump );
	PlayerInputComponent->BindAction( TEXT( "Shoot" ), EInputEvent::IE_Pressed, this, &AShooterCharacter::PlayerShoot );
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

void AShooterCharacter::PlayerShoot( )
{
	GunSpawn->GunShoot( );
}
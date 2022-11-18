// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIShooterController::BeginPlay( )
{
	Super::BeginPlay( );

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld( ), 0 );

	if ( AIBehaviorTree != nullptr )
	{
		RunBehaviorTree( AIBehaviorTree );
	}

	GetBlackboardComponent( )->SetValueAsVector( TEXT( "EnemyLocation" ), GetPawn( )->GetActorLocation( ) );
	
}

void AAIShooterController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld( ), 0 );

	bool IsLineOfSightTo = LineOfSightTo( PlayerPawn );

	if ( IsLineOfSightTo )
	{
		GetBlackboardComponent( )->SetValueAsVector( TEXT( "PlayerLocation" ), PlayerPawn->GetActorLocation( ) );
	}
	else
	{
		GetBlackboardComponent( )->ClearValue( TEXT( "PlayerLocation" ) );
	}
		
	
	
}

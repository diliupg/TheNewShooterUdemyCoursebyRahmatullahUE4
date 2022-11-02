// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"
#include "Kismet/GameplayStatics.h"

void AAIShooterController::BeginPlay( )
{
	Super::BeginPlay( );

	if ( AIBehaviorTree != nullptr )
	{
		RunBehaviorTree( AIBehaviorTree );
	}

}

void AAIShooterController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld( ), 0 );

	bool LineOfSight = LineOfSightTo( PlayerPawn );
	if ( LineOfSight )
	{
		SetFocus( PlayerPawn );
		MoveToActor( PlayerPawn, 300.f );
	}
	else

	{
		ClearFocus(EAIFocusPriority::Gameplay );
		StopMovement( );
	}
	
}

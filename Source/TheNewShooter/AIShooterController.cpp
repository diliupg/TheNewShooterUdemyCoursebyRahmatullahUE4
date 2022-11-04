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

	GetBlackboardComponent( )->SetValueAsVector( TEXT( "PlayerLocation" ), PlayerPawn->GetActorLocation() );
	GetBlackboardComponent( )->SetValueAsVector( TEXT( "PawnLocation" ), GetPawn()->GetActorLocation() );

}

void AAIShooterController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld( ), 0 );

	bool LineOfSight = LineOfSightTo( PlayerPawn );
	/*if ( LineOfSight )
	{
		SetFocus( PlayerPawn );
		MoveToActor( PlayerPawn, 300.f );
	}
	else

	{
		ClearFocus(EAIFocusPriority::Gameplay );
		StopMovement( );
	}*/
	
}

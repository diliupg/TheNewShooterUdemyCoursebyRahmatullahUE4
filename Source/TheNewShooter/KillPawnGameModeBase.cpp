// Fill out your copyright notice in the Description page of Project Settings.


#include "KillPawnGameModeBase.h"

void AKillPawnGameModeBase::PawnKilled( APawn* PawnKilled )
{
	Super::PawnKilled( PawnKilled );

	APlayerController* PlayerController = Cast<APlayerController>( PawnKilled->GetController( ) );
	if ( PlayerController != nullptr )
	{
		PlayerController->GameHasEnded( nullptr, false );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Enemy died" ) );
	}
}

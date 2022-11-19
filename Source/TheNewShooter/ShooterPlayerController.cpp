// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

void AShooterPlayerController::GameHasEnded( class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false */ )
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	UE_LOG( LogTemp, Warning, TEXT( "Player has died" ) );
}

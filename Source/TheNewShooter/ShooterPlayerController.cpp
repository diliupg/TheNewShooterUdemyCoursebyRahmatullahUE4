// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay( )
{
	HUD = CreateWidget( this, HUDBP );

	if ( HUD != nullptr ) { HUD->AddToViewport( ); }
}

void AShooterPlayerController::GameHasEnded( class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false */ )
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	if ( HUD != nullptr ) { HUD->RemoveFromViewport( ); }

	UUserWidget* LoserScreen = CreateWidget( this, LoserScreenBP );

	if ( LoserScreen != nullptr ) { LoserScreen->AddToViewport( ); }
}
 
// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded( class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false */ )
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	UUserWidget* LoserScreen = CreateWidget( this, LoserScreenBP );
	if ( LoserScreen != nullptr )
	{
		LoserScreen->AddToViewport( );
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THENEWSHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void GameHasEnded( class AActor* EndGameFocus = nullptr, bool bIsWinner = false ) override;

protected:

	virtual void BeginPlay( ) override;

private:
	//Widget
	UPROPERTY(EditAnywhere )
	TSubclassOf<class UUserWidget> LoserScreenBP;

	UPROPERTY( EditAnywhere )
	TSubclassOf<class UUserWidget> HUDBP;

	class UUserWidget* LoserScreen;
	class UUserWidget* HUD;

};


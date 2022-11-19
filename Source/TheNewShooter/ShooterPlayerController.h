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

protected:
	
	virtual void BeginPlay( ) override;

public:

	virtual void GameHasEnded( class AActor* EndGameFocus = nullptr, bool bIsWinner = false ) override;
	
private:

	UPROPERTY(EditAnywhere )
	TSubclassOf<UUserWidget> LoserScreenBP;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UUserWidget> HUDBP;

	class UUserWidget* HUD;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheNewShooterGameModeBase.h"
#include "KillPawnGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THENEWSHOOTER_API AKillPawnGameModeBase : public ATheNewShooterGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void PawnKilled( APawn* PawnKiled ) override;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheNewShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THENEWSHOOTER_API ATheNewShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void PawnKilled( APawn* PawnKiled );
};

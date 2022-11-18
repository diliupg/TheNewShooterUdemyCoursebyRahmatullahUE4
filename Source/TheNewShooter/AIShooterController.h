// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIShooterController.generated.h"

/**
 * 
 */
UCLASS()
class THENEWSHOOTER_API AAIShooterController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay( ) override;

public:

	virtual void Tick( float DeltaSeconds ) override;

private:
	UPROPERTY(EditAnywhere )
	class UBehaviorTree* AIBehaviorTree;
};

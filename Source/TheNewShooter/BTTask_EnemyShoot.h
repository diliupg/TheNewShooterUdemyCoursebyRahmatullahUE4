// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemyShoot.generated.h"

/**
 * 
 */
UCLASS()
class THENEWSHOOTER_API UBTTask_EnemyShoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY( )

public:

	UBTTask_EnemyShoot( );

protected:

	virtual EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) override;
	
};

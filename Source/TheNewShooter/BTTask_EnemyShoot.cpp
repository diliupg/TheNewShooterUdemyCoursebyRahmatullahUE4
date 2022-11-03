// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EnemyShoot.h"
#include "ShooterCharacter.h"
#include "AIShooterController.h"


UBTTask_EnemyShoot::UBTTask_EnemyShoot( )
{
	NodeName = TEXT( "Shoot" );
}

EBTNodeResult::Type UBTTask_EnemyShoot::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	Super::ExecuteTask( OwnerComp, NodeMemory );
	
	if ( OwnerComp.GetAIOwner( ) == nullptr ) { return EBTNodeResult::Failed; }

	AShooterCharacter*  Character = Cast<AShooterCharacter>( OwnerComp.GetAIOwner( )->GetPawn() );

	if ( Character == nullptr ) { return EBTNodeResult::Failed; }

	Character->ShootGun( );

	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KillPawnGameModeBase.h"

void AKillPawnGameModeBase::PawnKilled( APawn* PawnKiled )
{
	Super::PawnKilled( PawnKiled );

	UE_LOG(LogTemp, Warning, TEXT("Enemy killed:") )
}

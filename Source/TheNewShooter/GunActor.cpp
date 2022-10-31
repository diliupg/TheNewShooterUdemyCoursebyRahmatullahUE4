// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "Gun" ) );

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame 
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::GunShoot( )
{
	UE_LOG( LogTemp, Warning, TEXT( "Shoot" ) );
}


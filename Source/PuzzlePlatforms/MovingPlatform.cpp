// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	Direction = (GlobalTargetLocation - GetActorLocation()).GetSafeNormal();
	JourneyLength = (GlobalTargetLocation - StartLocation).Size();
	UE_LOG(LogTemp, Warning, TEXT("JourneyLength: %f"), JourneyLength)
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority()) {
		FVector Location = GetActorLocation();
		if ( (Location - StartLocation).Size() > JourneyLength) {
			Direction *= -1;
			FVector aux = GlobalTargetLocation;
			GlobalTargetLocation = StartLocation;
			StartLocation = aux;
		}

		SetActorLocation(Location + DeltaTime * Direction * Speed); 
	}
	}	

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
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority() && ActiveTriggers > 0) {
		FVector Location = GetActorLocation();
		if ( (Location - StartLocation).Size() > JourneyLength) {
			Direction *= -1;
			Swap(GlobalTargetLocation, StartLocation);
		}
		SetActorLocation(Location + DeltaTime * Direction * Speed); 
	}
	}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers--;
}

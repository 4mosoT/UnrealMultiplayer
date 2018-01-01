// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstace.h"
#include "Engine/Engine.h"



UPuzzlePlatformsGameInstace::UPuzzlePlatformsGameInstace(const FObjectInitializer &ObjectInitializer) {
	UE_LOG(LogTemp, Warning, TEXT("Constructor"))
}

void UPuzzlePlatformsGameInstace::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Init "))
}

void UPuzzlePlatformsGameInstace::Host()
{
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, TEXT("Hosting"));

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstace::Join(const FString& IPAddress)
{
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, FString::Printf(TEXT("Joining %s"), *IPAddress));
}

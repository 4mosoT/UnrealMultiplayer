// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstace.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"



UPuzzlePlatformsGameInstace::UPuzzlePlatformsGameInstace(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> PlatformBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (PlatformBPClass.Class != NULL) {
		MenuClass = PlatformBPClass.Class;
	}
}

void UPuzzlePlatformsGameInstace::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName())
}

void UPuzzlePlatformsGameInstace::LoadMenu()
{
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(Menu->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);

	PlayerController->bShowMouseCursor = true;

}

void UPuzzlePlatformsGameInstace::Host()
{
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, TEXT("Hosting"));

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstace::Join(const FString& IPAddress)
{
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, FString::Printf(TEXT("Joining %s"), *IPAddress));
	GetFirstLocalPlayerController()->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
}

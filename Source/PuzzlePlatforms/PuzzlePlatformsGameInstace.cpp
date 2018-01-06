// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstace.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"





UPuzzlePlatformsGameInstace::UPuzzlePlatformsGameInstace(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> PlatformBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	ConstructorHelpers::FClassFinder<UUserWidget> PlatformBPClassGameMenu(TEXT("/Game/MenuSystem/WBP_InGameMenu"));

	if (PlatformBPClass.Class != NULL && PlatformBPClassGameMenu.Class != NULL) {
		MenuClass = PlatformBPClass.Class;
		InGameMenuClass = PlatformBPClassGameMenu.Class;
	}
}

void UPuzzlePlatformsGameInstace::Init() {
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS != nullptr)	UE_LOG(LogTemp, Warning, TEXT("Online subsystem: %s"), *OSS->GetSubsystemName().ToString())
	SessionInterface = OSS->GetSessionInterface();
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstace::OnCreateSessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstace::OnFindSessionComplete);
}

void UPuzzlePlatformsGameInstace::LoadInGameMenu()
{
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstace::LoadMenuWidget()	
{
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	Menu->Setup();
	Menu->SetMenuInterface(this);
	
}

void UPuzzlePlatformsGameInstace::Host() 
{
	if (SessionInterface->GetNamedSession(SESSION_NAME)) SessionInterface->DestroySession(SESSION_NAME);
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bShouldAdvertise = true;
	SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
}

void UPuzzlePlatformsGameInstace::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't Create Session"))
		return;
	}
	if(Menu != nullptr)	Menu->Teardown();
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, TEXT("Hosting"));
	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstace::OnFindSessionComplete(bool Success)
{	
	TArray<FString> ServerNames;
	for (const FOnlineSessionSearchResult& Session : SessionSearch->SearchResults) {
		UE_LOG(LogTemp, Warning, TEXT("Find session: %s"), *Session.GetSessionIdStr())
			ServerNames.Add(Session.GetSessionIdStr());
		}
	UE_LOG(LogTemp, Warning, TEXT("Find session finish"))
	Menu->SetServerList(ServerNames);
}

void UPuzzlePlatformsGameInstace::Join(const FString& IPAddress)
{
	if (Menu != nullptr) {
		Menu->SetServerList({"Test1", "Test2"});
		//Menu->Teardown();
	}
	//GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::White, FString::Printf(TEXT("Joining %s"), *IPAddress));
	//GetFirstLocalPlayerController()->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstace::ReturnToMainMenu()
{
	GetFirstLocalPlayerController()->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstace::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	UE_LOG(LogTemp, Warning, TEXT("Find session start"))
}


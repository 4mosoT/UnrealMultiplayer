// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "PuzzlePlatformsGameInstace.generated.h"


class UMainMenu;
class UInGameMenu;
class FOnlineSessionSearch;

const static FName SESSION_NAME = TEXT("My session");
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstace : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	UPuzzlePlatformsGameInstace(const FObjectInitializer &ObjectInitializer);
	
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(int32 Index) override;
	 
	virtual void ReturnToMainMenu() override;

	virtual void RefreshServerList() override;

private:
	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;

	UMainMenu* Menu;
	UInGameMenu* InGameMenu;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};

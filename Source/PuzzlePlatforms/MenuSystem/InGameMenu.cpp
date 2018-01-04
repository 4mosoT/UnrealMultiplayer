// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"
#include "MenuInterface.h"


bool UInGameMenu::Initialize()
{
	bool Succes = Super::Initialize();
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMainMenu);

	return true;
}

void UInGameMenu::CancelPressed()
{
	Teardown();
}

void UInGameMenu::ReturnToMainMenu()
{
	Teardown();
	MenuInterface->ReturnToMainMenu();
}

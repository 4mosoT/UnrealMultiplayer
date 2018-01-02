// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "MenuInterface.h"


bool UMainMenu::Initialize()
{
	bool Succes = Super::Initialize();

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	return Succes;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr) MenuInterface->Host();
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface) {

	this->MenuInterface = MenuInterface;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"




void UMenuWidget::Setup()
{
	this->AddToViewport();
	PlayerController = GetWorld()->GetFirstPlayerController();
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();
	PlayerController->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);

}


void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface) {

	this->MenuInterface = MenuInterface;
}
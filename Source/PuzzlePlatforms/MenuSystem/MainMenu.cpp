// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"
#include "MenuInterface.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer) {

	ConstructorHelpers::FClassFinder<UUserWidget> BPRowClass(TEXT("/Game/MenuSystem/WBP_RowServer"));
	if(BPRowClass.Class != NULL) RowServerClass = BPRowClass.Class;

}


void UMainMenu::SetServerList(TArray<FString> ServerNameList)
{
	ServerList->ClearChildren();
	for (const FString& ServerName : ServerNameList) {
		UServerRow* RowServer = CreateWidget<UServerRow>(GetWorld(), RowServerClass);
		RowServer->ServerName->SetText(FText::FromString(ServerName));
		ServerList->AddChild(RowServer);
	}
}

bool UMainMenu::Initialize()
{
	bool Succes = Super::Initialize();

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenu);
	AcceptJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);




	return true;
}

void UMainMenu::HostServer()
{
	
	if (MenuInterface != nullptr) MenuInterface->Host();
}

void UMainMenu::OpenJoinMenu()
{
	MenuInterface->RefreshServerList();
	MenuSwitcher->SetActiveWidget(JoinMenu);


}

void UMainMenu::CancelJoinMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);

}

void UMainMenu::JoinServer()
{
	//FString IPAddress = IPAddressTextBox->GetText().ToString();
	//if (IPAddress.Len() > 0 && MenuInterface != nullptr) MenuInterface->Join(IPAddress); else IPAddressTextBox->SetText(FText::FromString(TEXT("You must enter a valid IP")));
	MenuInterface->Join(TEXT("Prueba"));

}

void UMainMenu::QuitGame()
{
	PlayerController->ConsoleCommand(TEXT("quit"), false);
}


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
	int32 i = 0;
	for (const FString& ServerName : ServerNameList) {
		UServerRow* RowServer = CreateWidget<UServerRow>(GetWorld(), RowServerClass);
		RowServer->ServerName->SetText(FText::FromString(ServerName));
		RowServer->Setup(this, i);
		ServerList->AddChild(RowServer);
		i++;
	}
}

void UMainMenu::SelectIndex(int32 Index)
{
	SelectedIndex = Index;
	UE_LOG(LogTemp, Warning, TEXT("Selecting Index: %i"), Index)
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenu);
	AcceptJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true & Success;
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
	if(SelectedIndex.IsSet()) MenuInterface->Join(SelectedIndex.GetValue());
}

void UMainMenu::QuitGame()
{
	PlayerController->ConsoleCommand(TEXT("quit"), false);
}


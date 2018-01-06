// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "MainMenu.h"

void UServerRow::Setup(UMainMenu * Parent, int32 Index)
{
	ParentMenu = Parent;
	this->Index = Index;
	MainButton->OnClicked.AddDynamic(this, &UServerRow::SelectMenuIndex);

}

void UServerRow::SelectMenuIndex()
{
	ParentMenu->SelectIndex(Index);
}



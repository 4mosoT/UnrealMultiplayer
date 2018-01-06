// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UTextBlock;
class UMainMenu;
class UButton;
	
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	UButton* MainButton;

	void Setup(UMainMenu* Parent, int32 Index);

private:

	UFUNCTION()
	void SelectMenuIndex();

	int32 Index;
	
	UPROPERTY()
	UMainMenu* ParentMenu;
	
};

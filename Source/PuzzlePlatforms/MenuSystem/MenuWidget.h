// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"


class IMenuInterface;
class APlayerController;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);
	void Setup();
	void Teardown();

protected:
	APlayerController* PlayerController;
	IMenuInterface* MenuInterface;

	
	
};

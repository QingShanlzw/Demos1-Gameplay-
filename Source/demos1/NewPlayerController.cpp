// Fill out your copyright notice in the Description page of Project Settings.


#include "NewPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ANewPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(MenuAsset)
	{
		Menu = CreateWidget<UUserWidget>(this,MenuAsset);
		
	}
	if(Menu)
	{
		//Menu->SetVisibility(ESlateVisibility::Hidden);
		Menu->AddToViewport();
		
	}
	
}



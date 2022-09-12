// Fill out your copyright notice in the Description page of Project Settings.


#include "OriginPlayerController.h"

#include "demos1Character.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AOriginPlayerController::BeginPlay()
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

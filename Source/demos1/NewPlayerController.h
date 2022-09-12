// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMOS1_API ANewPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget>MenuAsset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* Menu;
	protected:
	virtual void BeginPlay() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NewSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerSlot
{
	GENERATED_BODY()

	UPROPERTY()
	int CoinBank;
	UPROPERTY()
	FName CurLevel;
	
};
UCLASS()
class DEMOS1_API UNewSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FPlayerSlot PlayerSlot;
};

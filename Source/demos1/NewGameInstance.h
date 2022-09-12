// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NewGameInstance.generated.h"

/**
 * 
 */



UCLASS(Blueprintable,BlueprintType)
class DEMOS1_API UNewGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	int CoinCount;
	UPROPERTY(EditAnywhere)
	bool Level02Move;

	UNewGameInstance();
	virtual  ~UNewGameInstance() =default;

	UFUNCTION()
	int GetCoinCount();
	UFUNCTION()
	void SetCoinCount(int c);
	UFUNCTION()
    static UNewGameInstance* GetInstance();
	UFUNCTION()
	int PassLevel(FName Level);


	
};

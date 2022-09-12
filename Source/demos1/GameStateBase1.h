// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBase1.generated.h"

/**
 * 
 */
UCLASS()
class DEMOS1_API AGameStateBase1 : public AGameStateBase
{
	GENERATED_BODY()
public:
	AGameStateBase1();
	virtual ~AGameStateBase1()=default;
	UPROPERTY(EditAnywhere)
	int coinCount;
};

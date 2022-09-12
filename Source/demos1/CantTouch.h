// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CantTouch.generated.h"

UCLASS()
class DEMOS1_API ACantTouch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACantTouch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float RunningTime;
	UPROPERTY(EditAnywhere,Category="Varibles | X")
	float A1; 
	UPROPERTY(EditAnywhere,Category="Varibles | X")
	float B1;
	UPROPERTY(EditAnywhere,Category="Varibles | Y")
	float A2; 
	UPROPERTY(EditAnywhere,Category="Varibles | Y")
	float B2;
};

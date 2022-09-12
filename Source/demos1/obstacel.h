// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewGameInstance.h"
#include "GameFramework/Actor.h"
#include "obstacel.generated.h"

UCLASS()
class DEMOS1_API Aobstacel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aobstacel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* StaticMesh;
	float RunningTime;
	UPROPERTY(EditAnywhere,Category="Varibles | X")
	float A1; 
	UPROPERTY(EditAnywhere,Category="Varibles | X")
	float B1;
	UPROPERTY(EditAnywhere,Category="Varibles | Y")
	float A2; 
	UPROPERTY(EditAnywhere,Category="Varibles | Y")
	float B2;
	UPROPERTY(EditAnywhere,Category="Varibles | Z")
	float A3; 
	UPROPERTY(EditAnywhere,Category="Varibles | Z")
	float B3;
	UPROPERTY(EditAnywhere,Category="Varibles |  temp")
	int t =0;
	void disAble(bool isHide);
	
	UPROPERTY(EditAnywhere)
	bool IsHide;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp2.generated.h"

UCLASS()
class DEMOS1_API APickUp2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MyValue;
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* StaticMesh;
	float RunningTime;
	UPROPERTY(EditAnywhere,Category="Varibles")
	float A; 
	UPROPERTY(EditAnywhere,Category="Varibles")
	float B;
	UPROPERTY(EditAnywhere,Category="Varibles")
	FRotator rota;

};

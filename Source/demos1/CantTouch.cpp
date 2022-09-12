// Fill out your copyright notice in the Description page of Project Settings.


#include "CantTouch.h"

// Sets default values
ACantTouch::ACantTouch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACantTouch::BeginPlay()
{
	Super::BeginPlay();
	RunningTime =0.f;
}

// Called every frame
void ACantTouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += A1*FMath::Sin(B1*RunningTime);
	NewLocation.Y += A2*FMath::Sin(B2*RunningTime);
	SetActorLocation(NewLocation);
	RunningTime +=DeltaTime;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "obstacel.h"

#include "demos1Character.h"



// Sets default values
Aobstacel::Aobstacel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	RunningTime =0.f;
	IsHide =false;
	
}

// Called when the game starts or when spawned
void Aobstacel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aobstacel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += A1*FMath::Sin(B1*RunningTime);
	NewLocation.Y += A2*FMath::Sin(B2*RunningTime);
	NewLocation.Z += A3*FMath::Sin(B3*RunningTime);
	SetActorLocation(NewLocation);
	RunningTime +=DeltaTime;
    if(IsHide)
    {
    	t=(t+1) %800;
    	if(t>=0&&t<=500) disAble(true);
    	else disAble(false);
    }
	
}

void Aobstacel::disAble(bool isHide) 
{
	// Hides visible components
	SetActorHiddenInGame(!isHide);

	// Disables collision components
	SetActorEnableCollision(isHide);
	
}





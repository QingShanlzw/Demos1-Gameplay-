// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp2.h"

// Sets default values
APickUp2::APickUp2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyValue =3;
	StaticMesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	RunningTime =0.f;
	rota = FRotator(0.f,0.f,0.f);

}

// Called when the game starts or when spawned
void APickUp2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += A*FMath::Sin(B*RunningTime);
	SetActorLocation(NewLocation);
	AddActorLocalRotation(rota);
	RunningTime +=DeltaTime;
}


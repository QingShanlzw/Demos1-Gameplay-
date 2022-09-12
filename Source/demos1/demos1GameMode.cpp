// Copyright Epic Games, Inc. All Rights Reserved.

#include "demos1GameMode.h"
#include "demos1Character.h"
#include "GameStateBase1.h"
#include "NewPlayerController.h"
#include "UObject/ConstructorHelpers.h"

Ademos1GameMode::Ademos1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BPNewPlayerController"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = AGameStateBase1::StaticClass();
	
}

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "StealthPrototypeGameMode.h"
#include "StealthPrototypePlayerController.h"
#include "StealthPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStealthPrototypeGameMode::AStealthPrototypeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AStealthPrototypePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
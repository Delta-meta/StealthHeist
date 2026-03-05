// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthHeistGameMode.h"
#include "StealthHeistCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStealthHeistGameMode::AStealthHeistGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

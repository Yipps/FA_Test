// Copyright Epic Games, Inc. All Rights Reserved.

#include "FA_TestGameMode.h"
#include "FA_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFA_TestGameMode::AFA_TestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

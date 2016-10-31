// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TeamShrug.h"
#include "TeamShrugGameMode.h"
#include "TeamShrugHUD.h"
#include "TeamShrugCharacter.h"

ATeamShrugGameMode::ATeamShrugGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATeamShrugHUD::StaticClass();
}

// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TeamShrug.h"
#include "TeamShrugHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ATeamShrugHUD::ATeamShrugHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void ATeamShrugHUD::DrawHUD()
{
	Super::DrawHUD();
}


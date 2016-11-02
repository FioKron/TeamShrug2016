// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TeamShrugSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TEAMSHRUG_API UTeamShrugSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerID;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int PlayerEndScore;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};

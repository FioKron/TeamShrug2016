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

	// Properties:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerID;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int PlayerEndScore;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int UserIndex;

	// Functions:
	

	/**
		Saving and loading the game:
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Player Stat."), Category = Highscore)
	void SaveScore(FString NewPlayerID, int NewPlayerEndScore, 
		FString NewSaveSlotName, int NewUserIndex);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Player Stat."), Category = Highscore)
	void LoadScore(FString SaveGameSaveSlotName, int SaveGameUserIndex);
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString PlayerID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	int PlayerEndScore;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	FString SaveSlotName;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	int UserIndex;

	// Functions:

	UTeamShrugSaveGame();

	/**
		Saving and loading the game:
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Game To Slot"), Category = Highscore)
	void SaveScore(FString NewPlayerID, int NewPlayerEndScore);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From Slot"), Category = Highscore)
	void LoadScore(FString SaveGameSaveSlotName, int SaveGameUserIndex);	
};

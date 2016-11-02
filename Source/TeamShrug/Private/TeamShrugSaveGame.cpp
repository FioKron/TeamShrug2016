// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamShrug.h"
#include "TeamShrugSaveGame.h"


void UTeamShrugSaveGame::SaveScore(FString NewPlayerID, int NewPlayerEndScore,
	FString NewSaveSlotName, int NewUserIndex)
{
	PlayerID = NewPlayerID;
	PlayerEndScore = NewPlayerEndScore;
	SaveSlotName = NewSaveSlotName;
	UserIndex = NewUserIndex;
}

void UTeamShrugSaveGame::LoadScore(FString SaveGameSaveSlotName, int SaveGameUserIndex)
{

}


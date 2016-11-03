// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamShrug.h"
#include "TeamShrugSaveGame.h"


UTeamShrugSaveGame::UTeamShrugSaveGame()
{
	SaveSlotName = "TestSaveSlot";
	UserIndex = 0;
}

void UTeamShrugSaveGame::SaveScore(FString NewPlayerID, int NewPlayerEndScore)
{
	UTeamShrugSaveGame* SaveGamePointer = Cast<UTeamShrugSaveGame>(UGameplayStatics::CreateSaveGameObject(UTeamShrugSaveGame::StaticClass()));

	SaveGamePointer->PlayerID = NewPlayerID;
	SaveGamePointer->PlayerEndScore = NewPlayerEndScore;

	UGameplayStatics::SaveGameToSlot(SaveGamePointer, SaveGamePointer->SaveSlotName, SaveGamePointer->UserIndex);
}

void UTeamShrugSaveGame::LoadScore(FString SaveGameSaveSlotName, int SaveGameUserIndex)
{

}


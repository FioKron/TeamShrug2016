// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamShrug.h"
#include "../Public/Mine.h"


// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**
	PrimaryReference = CreateDefaultSubobject<UStaticMeshComponent>("PrimaryReference");
	PrimaryReference->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	PrimaryReference->SetVisibility(true);
	PrimaryReference->SetHiddenInGame(false);
	PrimaryReference->SetSimulatePhysics(false);
	PrimaryReference->bGenerateOverlapEvents = true;
	*/
}

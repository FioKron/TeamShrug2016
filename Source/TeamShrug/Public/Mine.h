// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class TEAMSHRUG_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	

	// Functions:

	// Sets default values for this actor's properties
	AMine();


	// Properties:

	// For collision and positional reference whilst playing: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ReferenceComponent)
	class USphereComponent* PrimaryReference;
	
};

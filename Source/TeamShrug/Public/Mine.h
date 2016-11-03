// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class TEAMSHRUG_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PrimaryReference)
	class UStaticMeshComponent* PrimaryReference;
	*/
	AMine();

};

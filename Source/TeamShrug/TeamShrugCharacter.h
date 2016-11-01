// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Public/Mine.h"
#include "TeamShrugCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ATeamShrugCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// So that the 'Hit' method would not have to receive a call from Blueprint
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	)override;

	// For handling tick behavior
	virtual void Tick(float DeltaTime)override;

public:
	
	// Functions:

	ATeamShrugCharacter();

	virtual void BeginPlay();
	
	/** 
		For the 4 respective box components
		on this character signifying the end 
		of mine overlap:

		@Param: AActor* OverlappingActor: The actor
		to cast to AMine, if successful, this function has results
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Mine Overlap Ends"), Category = Proximity)
	void EndMineOverlap(AActor* OverlappingActor);

	/**
		For the 5 respective box components
		on this character signifying the beginning
		of mine overlap:

		@Params: AActor* OverlappingActor: The actor
		to cast to AMine, if successful, this function has results

		FString ActiveBox: To set DebugText
		to the current active box

		float Intensity: The intensity of controller vibration
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Mine Overlap Begins"), Category = Proximity)
	void BeginMineOverlap(AActor* OverlappingActor, FString ActiveBox, float NewIntensity);

	// Properties:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATeamShrugProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/**
		For debug messages
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Debug)
	FString DebugText;

	/**
		Flags:
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Flags)
	bool IsOverlap;

	/**
		For the intensity of controller vibration (rumble):
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Feedback)
	float VibrationIntensity;

	/**
		The minimum time (in seconds), that the Player has, to defuse the bomb:
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LimitingFactors)
	float MinimumCountdown;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};


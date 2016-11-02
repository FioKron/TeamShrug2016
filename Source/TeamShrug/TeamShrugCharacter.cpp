// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TeamShrug.h"
#include "TeamShrugCharacter.h"
#include "TeamShrugProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATeamShrugCharacter

ATeamShrugCharacter::ATeamShrugCharacter()
{
	// For tick to function:
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);
	
	// Initilise the custom member parameters:
	DebugText.Add("Default");
	VibrationIntensity = 0.05f;
	MinimumCountdown = 4.0f;
	Countdown = 0.0f;
	DefusalTime = 5.0f;
	bDefusing = false;
	CurrentScore = 0;
	TickTimer = 0.0f;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

/**
	Both of these functions check for mine proximity:
*/
void ATeamShrugCharacter::BeginMineOverlap(AActor* OverlappingActor, FString ActiveBox, float NewIntensity, float NewMinimumCountdown)
{
	if (Cast<AMine>(OverlappingActor)->IsValidLowLevel())
	{
		bIsOverlap = true;
		MinimumCountdown = NewMinimumCountdown;
		DebugText[0] = ActiveBox;
		
		// For the handling the new debug message ('Out of Range!'):
		if (DebugText[0] != "Box1" && !(DebugText.IsValidIndex(1)))
		{
			DebugText.Add("Out of Range!");
		}
		else if (DebugText[0] != "Box1" && DebugText.IsValidIndex(1))
		{
			DebugText[1] = "Out of Range!";
		}
		
		VibrationIntensity = NewIntensity;	
	}	
}

void ATeamShrugCharacter::EndMineOverlap(AActor* OverlappingActor)
{
	if (Cast<AMine>(OverlappingActor)->IsValidLowLevel())
	{
		bIsOverlap = false;
		DebugText[0] = "None";
		MinimumCountdown = 4.0f;
		if (!(DebugText.IsValidIndex(1)))
		{
			DebugText.Add("Nothing to Defuse!");
		}
		else if (DebugText.IsValidIndex(1))
		{
			DebugText[1] = "Nothing to Defuse!";
		}
	}
}

void ATeamShrugCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{	
	AMine* IsOtherMineCheck = Cast<AMine>(Other);

	if (IsOtherMineCheck->IsValidLowLevel())
	{
		DebugText[0] = "Dead";	
	}
}

void ATeamShrugCharacter::Tick(float DeltaTime)
{
	// For timing:
	TickTimer += DeltaTime;
	
	// For avoiding null pointer exceptions:
	if (GEngine)
	{
		if (bDefusing)
		{
			
		}
		else
		{

		}

		if (TickTimer >= 1.0f)
		{
			for (int Counter = 0; Counter < DebugText.Num(); Counter++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, DebugText[Counter]);
			}
			
			TickTimer = 0.0f;
		}
		
		if (bIsOverlap)
		{
			APlayerController* PlayerCharacterController = Cast<APlayerController>(GetController());

			if (PlayerCharacterController->IsValidLowLevel())
			{
				PlayerCharacterController->PlayDynamicForceFeedback(VibrationIntensity, 0.1f, 
					true, true, true, true, EDynamicForceFeedbackAction::Type::Start, 
					FLatentActionInfo::FLatentActionInfo());
			}
		}
	}
}

void ATeamShrugCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATeamShrugCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATeamShrugCharacter::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &ATeamShrugCharacter::OnFire);
	}

	InputComponent->BindAxis("MoveForward", this, &ATeamShrugCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATeamShrugCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATeamShrugCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATeamShrugCharacter::LookUpAtRate);
}

void ATeamShrugCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<ATeamShrugProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void ATeamShrugCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATeamShrugCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void ATeamShrugCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y * BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void ATeamShrugCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATeamShrugCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATeamShrugCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATeamShrugCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ATeamShrugCharacter::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATeamShrugCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &ATeamShrugCharacter::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATeamShrugCharacter::TouchUpdate);
	}
	return bResult;
}

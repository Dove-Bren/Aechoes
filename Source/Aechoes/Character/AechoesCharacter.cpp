// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "AechoesCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AAechoesCharacter

AAechoesCharacter::AAechoesCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UOverworldCharMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

}

void AAechoesCharacter::BeginPlay() {
	Super::BeginPlay();
	AOCharacterController *controller = GetWorld()->SpawnActor<AOCharacterController>(
		AOCharacterController::StaticClass(),
		GetActorLocation(),
		GetActorRotation()
		);

	controller->Possess(this);
}

/**
* Checks whether this blocks _movement_ for the given character
* @param cin the character trying to move past this obstacle
* @return true when the character can pass
**/
bool AAechoesCharacter::CanPass(AAechoesCharacter *cin)
{
	return false;
}

/**
* Checks whether this blocks _sight_ for the given character
* @param char the character trying to see/cast through this obstacle
* @param cast whether this check is used for LOS instead of just sight
* @return true when the character can see through
**/
bool AAechoesCharacter::CanSeeThrough(AAechoesCharacter *cin, bool cast)
{
	return false;
}

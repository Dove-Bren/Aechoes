// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "OverworldCamera.h"
#include "../Character/LivingCharacter.h"
#include "../AechoesGameMode.h"
#include "OverworldController.generated.h"

/**
 * Player controller for usual, overworld control and mechanics
 */
UCLASS()
class AECHOES_API AOverworldController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** 
	 * Current control target 
	 * This is different from the possessed pawn, since we're possessing the camera
	 **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Controls)
	ALivingCharacter *CCharacter;

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handles left clicks **/
	void OnSelectClick();

	/** Handles right clicks **/
	void OnActionClick();
	
	/** Called for up/down input */
	void MoveUp(float Rate);

	/** Called for side to side input */
	void MoveRight(float Rate);

	/**
	* Called via input to go up or down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void MoveUpRate(float Rate);

	/**
	* Called via input to turn look side-to-side at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void MoveRightRate(float Rate);

	void ZoomIn();

	void ZoomOut();
	
	virtual void SetupInputComponent() override;

	virtual void TickActor(float DeltaTime,
		enum ELevelTick TickType,
		FActorTickFunction & ThisTickFunction
	) override;
	
public:
	AOverworldController();

	/**
	 * Sets the currently controlled character
	 * @param in The new character to control
	 **/
	UFUNCTION(BlueprintCallable, Category = Controls)
	void SetControl(ALivingCharacter *in);
	
};

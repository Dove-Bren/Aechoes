// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "LivingCharacter.h"
#include "HudLivingOverlay.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API AHudLivingOverlay : public AHUD
{
	GENERATED_BODY()

	/** The character to follow and display information about **/
	ALivingCharacter character;

protected:

public:

	/** Creates a new overlay, with the given character **/
	UFUNCTION(BlueprintCallable, Category = Constructors)
	AHudLivingOverlay(ALivingCharacter character);
	
	/** Fetch the current character object of this overlay
	 * @return the character being reported on
	 **/
	UFUNCTION(BlueprintCallable, Category = Getters)
	ALivingCharacter getCharacter();

	/** Replace the current character object with the provided character
	* @param character the character to set this overlay to report on
	**/
	UFUNCTION(BlueprintCallable, Category = Setters)
	void setCharacter(ALivingCharacter character);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatableCharacter.h"
#include "Attack.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttack : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class AECHOES_API IAttack
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
    /** Return the range of the attack **/
    uint8 getRange();

    /** Perform the attack, with the given parameters **/
    bool perform(ACombatableCharacter *source, FVector *loc);
	
};

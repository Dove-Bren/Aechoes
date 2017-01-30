// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Character/CombatableCharacter.h"
#include "DamageVector.h"
#include "Attack.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
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
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    uint8 getRange();

    /** 
     * Perform the attack, with the given parameters 
     * The attack is expected to perform all range sweeping, etc
     * @param source The source of the attack, used for power calculations
     * @param loc The location the attack was performed around
     * @return false on complete failure (0 damage, etc). True otherwise
     **/
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    bool perform(ACombatableCharacter *source, FVector loc);

    /** Perform damage calculations resulting in a pool of DamageVectors,
     * But return them for inspection instead 
     * @param source The source of the attack, for damage calculations
     * @return An array of resultant Damage Vectors
     **/
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    TArray<FDamageVector> findDamages(ACombatableCharacter *source);


    /** Return the name of the attack **/
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    FName getName();

    /** Fetch the description of the attack **/
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    FText getDesc();

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "../Character/CombatableCharacter.h"
#include "../Mechanics/DamageVector.h"
#include "Attack.generated.h"

class ACombatableCharacter;

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
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

public:
	
    /** Return the range of the attack **/
    UFUNCTION(BlueprintImplementableEvent, Category = Combat)
    uint8 getRange();

	/** Can this attack target the caster. Ignored if range = 0 **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	uint8 getTargetSelf();

	/** Does this attack require line of sight **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	uint8 needsLOS();

	/**
	 * Checks whether this attack can be cast on the provided target
	 * @param targ The targeted area
	 * @return Whether the attack can be used on the given cell
	 **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	bool canTarget(ACombatableCharacter *source, FVector loc);


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

	/** Initialize the Attack to the start of a turn **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void initTurn();

	/** Fetch the attack ID for this attack, for map lookups, etc **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	int32 getKey();

	/** Force the key of this attack to be the pr ovided key. **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void changeKey(int32 newKey);
	
};

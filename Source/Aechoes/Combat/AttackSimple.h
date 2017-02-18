#pragma once

#include "Attack.h"
#include "DamageVector.h"
#include "AttackSimple.generated.h"

UCLASS()
class UAttackSimple : public UStruct, public IAttack
{

    GENERATED_BODY()

protected:
    /** The name of this attack **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    FName Name;

    /** The description for this attack **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    FText Description;

    /** Range of this attack **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 Range;

    /** Array of damage vectors that are the base attack values
     * for this attack **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    TArray<FDamageVector> BaseVectors;

public:
    UAttackSimple();

    UAttackSimple(FName name, FText desc, uint8 range);

    ~UAttackSimple();

    /* Builder Methods*/

	/** Set the name of this attack
	 * @return this Instance, for chaining **/
	UAttackSimple *name(FName inName);

	/** Set the description of this attack
	 * @return this Instance, for chaining **/
	UAttackSimple *desc(FText inDesc);

	/** Set the range of this attack 
	 * @return this Instance, for chaining **/
	UAttackSimple *range(uint8 range);

    /** Adds a damage vector to this attack's list of vectors
     * @return This instance, for chaining **/
    UAttackSimple *add(FDamageVector vector);

    /** Adds a damage vector created from the passed arguments to base vectors 
     * @return This instance, for chaining **/
    UAttackSimple *add(DamageType type, int32 amount);

    /**********************************
     * Attack Interface
     **********************************/

    /** Return the range of the attack **/
    uint8 getRange();

    /**
    * Perform the attack, with the given parameters
    * The attack is expected to perform all range sweeping, etc
    * @param source The source of the attack, used for power calculations
    * @param loc The location the attack was performed around
    * @return false on complete failure (0 damage, etc). True otherwise
    **/
    bool perform(ACombatableCharacter *source, FVector loc);

    /** Perform damage calculations resulting in a pool of DamageVectors,
    * But return them for inspection instead
    * @param source The source of the attack, for damage calculations
    * @return An array of resultant Damage Vectors
    **/
    TArray<FDamageVector> findDamages(ACombatableCharacter *source);

    /** Return the name of the attack **/
    FName getName();

    /** Fetch the description of the attack **/
    FText getDesc();
};


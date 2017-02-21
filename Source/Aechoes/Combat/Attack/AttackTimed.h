#pragma once

#include "Attack.h"
#include "../Mechanics/DamageRange.h"
#include "AttackTimed.generated.h"

UCLASS()
class UAttackTimed : public UAttackSimple
{

    GENERATED_BODY()

protected:
    /** How many times per turn this attack can be used **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 MaxPerTurn;

    /** How many times per turn per character this ttack can be used **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 MaxPerChar;

	/** local indexer of current per-turn usages **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	uint8 CurrentPerTurn;

    /** Local map to keep track of casts-per-player **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    TMap<ACombatableCharacter *, uint8> CharMap;

public:
	UAttackTimed();

	UAttackTimed(FName name, FText desc, uint8 range);

    ~UAttackTimed();

    /* Builder Methods*/

	/** Set max per-turn usage of this attack
	 * @return this Instance, for chaining **/
	UAttackTimed *perTurn(uint8 max);

	/** Set max per-character usage of this attack
	 * @return this Instance, for chaining **/
	UAttackTimed *perChar(uint8 max);

	/** Can this attack target the given location **/
	virtual bool canTarget(ACombatableCharacter *source, FVector loc) override;

	virtual bool perform(ACombatableCharacter *source, FVector loc) override;

	virtual void initTurn() override;
};


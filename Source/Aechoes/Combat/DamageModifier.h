#pragma once

#include "DamageVector.h"
#include "DamageModifier.generated.h"

UENUM(BlueprintType)
enum class DamageCheckType : uint8
{
	ON_ATTACK,
	ON_DEFEND,
	ALWAYS
};

UENUM(BlueprintType)
enum class DamagePass : uint8
{
	CONSTANT_PASS,
	SCALE_PASS,
	FINAL_PASS
};

USTRUCT(Atomic, BlueprintType)
struct FDamageModifier
{
    GENERATED_USTRUCT_BODY()

public:

	/** Multiplier applied by this modifier **/
	UPROPERTY(BlueprintReadWrite, Category = "Core")
    float Scale;

	/** Literal added to damage by this modifier **/
	UPROPERTY(BlueprintReadWrite, Category = "Core")
	int32 Offset;

	/** Damage type that this modifier applies to **/
	UPROPERTY(BlueprintReadWrite, Category = "Core")
    DamageType DamageFilter;

	/** When this modifier should apply **/
	UPROPERTY(BlueprintReadWrite, Category = "Core")
	DamageCheckType ApplyType;

	/** Time left on this modifier before it expires **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Core")
	int32 TurnsLeft;

	/** Construct a FDamageModifier **/
	//UFUNCTION(BlueprintCallable, Category = "Damage")
    static FORCEINLINE FDamageModifier make(float scale, int32 offset, int32 duration,
		DamageType type, DamageCheckType applyType)
    {
		FDamageModifier mod;

		mod.Offset = offset;
		mod.Scale = scale;
		mod.ApplyType = applyType;
        mod.DamageFilter = type;
		mod.TurnsLeft = duration;

        return mod;
	};

	/**
	 * Queries whether this modifier would apply to the given parameters
	 * Checks damage type and attack type
	 * @param inVector the checked damage vector
	 * @param isAttack Is this an attack? If false, assumes it's defense
	 * @return True when the modifier applies; false otherwise
	 **/
	bool CanApply(FDamageVector const &inVector, bool isAttack);

	/**
	 * Applies the modifier to the provided vector.
	 * Does not check whether this modifier is supposed to apply. Relies
	 * on user previously checking CanApply
	 * @param input The vector to apply to
	 * @param The pass type, to determine which factor to apply
	 **/
	void Apply(FDamageVector &input, DamagePass passType);

	/**
	 * Event fired at the start of a character's turn to which this
	 * modifier is attached.
	 * This can be used for start-of-turn effects, but it's main purpose is
	 * to keep track of turns and repeal itself when it's out of duration.
	 * @return Whether to remove this modifier (e.g. it expired) or not. True
	 *         will remove the modifier from the list of active effects
	 **/
	bool TurnTick();


};
#pragma once

#include "DamageVector.h"
#include "DamageRange.generated.h"


UENUM(BlueprintType)
enum class ERangeSelection : uint8
{
	RANDOM,
	MIN,
	MAX
};

/**
 * Holds a range of values used to produce FDamageVectors when casting a spell.
 **/
USTRUCT(Atomic, BlueprintType)
struct FDamageRange
{
    GENERATED_USTRUCT_BODY()

    int32 min;

	int32 max;

    DamageType damageType;

    static FDamageRange make(int32 min, int32 max, DamageType type)
    {
		FDamageRange vect;

		vect.min = min;
		vect.max = max;

		if (max < min) {
			vect.max = min;
			vect.min = max;
		}

        vect.damageType = type;

        return vect;
    }

	FDamageVector Roll(ERangeSelection sel = ERangeSelection::RANDOM)
	{
		int32 amt = 0;
		switch (sel) {
		case ERangeSelection::MIN:
			amt = min;
			break;
		case ERangeSelection::MAX:
			amt = max;
			break;
		case ERangeSelection::RANDOM:
		default:
			amt = FMath::RandRange(min, max);
			break;
		}

		return FDamageVector::make(amt, damageType);
	}

};
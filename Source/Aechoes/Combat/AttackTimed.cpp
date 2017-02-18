
#include "Aechoes.h"
#include "../Character/CombatableCharacter.h"
#include "AttackTimed.h"

#define LOCTEXT_NAMESPACE "COMBAT"

UAttackTimed::UAttackTimed() : UAttackSimple::UAttackSimple()
{
	this->MaxPerTurn = 1;
	this->MaxPerChar = 1;
}

UAttackTimed::UAttackTimed(FName name, FText desc, uint8 range)
	: UAttackSimple::UAttackSimple(name, desc, range)
{
	this->MaxPerTurn = 1;
	this->MaxPerChar = 1;
}


UAttackTimed::~UAttackTimed()
{
    
}

bool UAttackTimed::perform(ACombatableCharacter * source, FVector loc)
{
	bool good = Super::perform(source, loc);

	CurrentPerTurn++;

    return good;
}

bool UAttackTimed::canTarget(FVector loc)
{
	if (!Super::canTarget(loc))
		return false;

	if (CurrentPerTurn < MaxPerTurn) {
				
		//check per-character usage
		//TODO

	}

	return false;
}

void UAttackTimed::initTurn()
{
	Super::initTurn();
	CurrentPerTurn = 0;
	CharMap.Empty();
}



#undef LOCTEXT_NAMESPACE
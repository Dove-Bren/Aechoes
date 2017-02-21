
#include "Aechoes.h"
#include "../../Character/CombatableCharacter.h"
#include "../../AechoesGlobals.h"
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

bool UAttackTimed::canTarget(ACombatableCharacter *source, FVector loc)
{
	if (!Super::canTarget(source, loc))
		return false;

	if (CurrentPerTurn < MaxPerTurn) {
				
		UWorldGrid *grid = UAechoesGlobals::FetchGrid();
		AObstacle *o = grid->get(loc.X, loc.Y);
		ACombatableCharacter *CChar = Cast<ACombatableCharacter>(o);
		if (!CChar)
			return true; //not something we track even

		uint8 count = 0;
		if (this->CharMap.Find(CChar) != nullptr) {
			count = *(this->CharMap.Find(CChar));
		}

		if (count < MaxPerChar) {
			CharMap.Add(CChar, count++);
			return true;
		}

		return false;

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
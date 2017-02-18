
#include "Aechoes.h"
#include "../Character/CombatableCharacter.h"
#include "../AechoesGlobals.h"
#include "AttackSimple.h"

#define LOCTEXT_NAMESPACE "COMBAT"

UAttackSimple::UAttackSimple()
{
    this->Name = FName(TEXT("Nameless Single Attack"));

    this->Description = LOCTEXT("DefAttackSingleDesc", "Attacks a single target.");

    this->Range = 1;

    //this->BaseVectors = TArray<FDamageVector>();
}

UAttackSimple::UAttackSimple(FName name, FText desc, uint8 range)
{
	this->Name = name;
	this->Description = desc;
	this->Range = range;
}


UAttackSimple::~UAttackSimple()
{
    
}

UAttackSimple * UAttackSimple::add(FDamageRange vector)
{
    this->BaseVectors.Add(vector);
    return this;
}

UAttackSimple * UAttackSimple::add(DamageType type, int32 amount)
{
	return this->add(type, amount, amount);
}

UAttackSimple * UAttackSimple::add(DamageType type, int32 min, int32 max)
{
	this->BaseVectors.Add(FDamageRange::make(min, max, type));
	return this;
}

uint8 UAttackSimple::getRange()
{
    return this->Range;
}

bool UAttackSimple::perform(ACombatableCharacter * source, FVector loc)
{
    TArray<FDamageVector> array = this->findDamages(source);

    //TODO
    //Get the character in the location
    //Then, apply resistances

    //Then check if 0's. If so, return false. Else apply and return true.

	for (FDamageVector v : array) {
		UE_LOG(LogTemp, Warning, TEXT("Damage vector: [%d, %d]"), (uint8) v.damageType, v.amount);
	}

    return true;
}

TArray<FDamageVector> UAttackSimple::findDamages(ACombatableCharacter * source)
{
	TArray<FDamageVector> VArray;
	FDamageVector cache;
	//float scale;
	
	if (BaseVectors.Num() > 0) {
		for (FDamageRange range : BaseVectors) {
			cache = range.Roll();

			//!! Leave alone for later review !!//
			//TODO//

			/*scale = source->getStats()->getModifier(cache.damageType);
			cache.amount = (int32)((float) cache.amount * scale);*/

			VArray.Add(cache);

		}

		VArray = source->AugmentDamages(VArray);
	}

    

    return VArray;
}

FName UAttackSimple::getName()
{
    return this->Name;
}

FText UAttackSimple::getDesc()
{
    return this->Description;
}

UAttackSimple *UAttackSimple::name(FName inName)
{
	this->Name = inName;
	return this;
}

UAttackSimple *UAttackSimple::desc(FText inDesc)
{
	this->Description = inDesc;
	return this;
}

UAttackSimple *UAttackSimple::range(uint8 range)
{
	this->Range = range;
	return this;
}

/** Can this attack target the caster. Ignored if range = 0 **/
bool UAttackSimple::getTargetSelf()
{
	return this->TargetSelf;
}

/** Does this attack require line of sight **/
bool UAttackSimple::needsLOS()
{
	return this->RequireLOS;
}

/** Sets whether this attack can target the caster
	* @return This instance, for chaining **/
UAttackSimple *UAttackSimple::targetSelf(bool canTargetSelf)
{
	this->TargetSelf = canTargetSelf;
	return this;
}

/** Sets whether this attack requires line of sight
* @return This instance, for chaining **/
UAttackSimple *UAttackSimple::requireLOS(bool needLos)
{
	this->RequireLOS = needLos;
	return this;
}

UAttackSimple * UAttackSimple::targetEmpty(bool canTarget)
{
	this->TargetEmpty = canTarget;
	return this;
}

bool UAttackSimple::PerformOnCell(ACombatableCharacter *source, FVector loc)
{
	return this->perform(source, loc);
}

bool UAttackSimple::CanTargetCell(ACombatableCharacter *source, FVector loc)
{
	return canTarget(source, loc);
}

bool UAttackSimple::canTarget(ACombatableCharacter *source, FVector loc)
{
	//Only check we have is is it empty, and can we target empty?
	if (TargetEmpty)
		return true;

	UWorldGrid *grid = UAechoesGlobals::FetchGrid(source->GetWorld());
	if (!grid) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to get grid object!"));
		return true;
	}


	if (grid->get(loc.X, loc.Y) != nullptr)
		return true;

	return false;
}

void UAttackSimple::initTurn()
{
	; //Nothing to do
}


#undef LOCTEXT_NAMESPACE
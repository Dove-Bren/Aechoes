
#include "Aechoes.h"
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

UAttackSimple * UAttackSimple::add(FDamageVector vector)
{
    this->BaseVectors.Add(vector);
    return this;
}

UAttackSimple * UAttackSimple::add(DamageType type, int32 amount)
{
    this->BaseVectors.Add(FDamageVector::make(amount, type));
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

    return true;
}

TArray<FDamageVector> UAttackSimple::findDamages(ACombatableCharacter * source)
{
    TArray<FDamageVector> array = this->BaseVectors;

    float scale;
    for (FDamageVector vector : array) {
        scale = source->getStats()->getModifier(vector.damageType);
        vector.amount = (int32) ( (float) vector.amount * scale );
    }

    return array;
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
uint8 UAttackSimple::getTargetSelf()
{
	return this->TargetSelf;
}

/** Does this attack require line of sight **/
uint8 UAttackSimple::needsLOS()
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



#undef LOCTEXT_NAMESPACE
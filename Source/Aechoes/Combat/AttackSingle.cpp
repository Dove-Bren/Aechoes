
#include "Aechoes.h"
#include "AttackSingle.h"

#define LOCTEXT_NAMESPACE "COMBAT"

UAttackSingle::UAttackSingle()
{
    this->name = FName(TEXT("Nameless Single Attack"));

    this->description = LOCTEXT("DefAttackSingleDesc", "Attacks a single target.");

    this->range = 1;

    this->baseVectors = TArray<FDamageVector>();
}


UAttackSingle::~UAttackSingle()
{
    
}

UAttackSingle * UAttackSingle::add(FDamageVector vector)
{
    this->baseVectors.Add(vector);
    return this;
}

UAttackSingle * UAttackSingle::add(DamageType type, int32 amount)
{
    this->baseVectors.Add(FDamageVector::make(amount, type));
    return this;
}

uint8 UAttackSingle::getRange()
{
    return this->range;
}

bool UAttackSingle::perform(ACombatableCharacter * source, FVector loc)
{
    TArray<FDamageVector> array = this->findDamages(source);

    //TODO
    //Get the character in the location
    //Then, apply resistances

    //Then check if 0's. If so, return false. Else apply and return true.

    return true;
}

TArray<FDamageVector> UAttackSingle::findDamages(ACombatableCharacter * source)
{
    TArray<FDamageVector> array = this->baseVectors;

    float scale;
    for (FDamageVector vector : array) {
        scale = source->getStats()->getModifier(vector.damageType);
        vector.amount = (int32) ( (float) vector.amount * scale );
    }

    return array;
}

FName UAttackSingle::getName()
{
    return this->name;
}

FText UAttackSingle::getDesc()
{
    return this->description;
}



#undef LOCTEXT_NAMESPACE
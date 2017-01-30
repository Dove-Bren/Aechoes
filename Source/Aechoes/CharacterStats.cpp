// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "CharacterStats.h"


UCharacterStats::UCharacterStats()
{
    this->Strength = 0;
    this->Agility = 0;
    this->Dexterity = 0;
    this->Intelligence = 0;
    this->Passion = 0;
    this->Wisdom = 0;
    this->Vitality = 0;
}

UCharacterStats::UCharacterStats(int32 strength, int32 agility,
                int32 dexterity, int32 intel, int32 passion, int32 wisdom,
                int32 vit)
{
    this->Strength = strength;
    this->Agility = agility;
    this->Dexterity = dexterity;
    this->Intelligence = intel;
    this->Passion = passion;
    this->Wisdom = wisdom;
    this->Vitality = vit;
}

int32 UCharacterStats::getInitiative()
{
    /*
    * Initiative = Intelligence + (.5 * Agility)
    */
    return this->Intelligence + (this->Agility / 2); //int div cuts frac
}

int32 UCharacterStats::getFortune()
{
    /* Fortune = Passion + (.5 * Agility) + (.5 * Intelligence) */
    return this->Passion + (this->Agility / 2) + (this->Intelligence / 2);
}

int32 UCharacterStats::getHealth()
{
    /* Health = (Vitality * 5) */
    return this->Vitality * 5;
}

int32 UCharacterStats::getDodgePower()
{
    /* DodgePower = (2 * Agility) + (.5 * Dexterity) */
    return (this->Agility * 2) + (this->Dexterity / 2);
}

int32 UCharacterStats::getLockPower()
{
    /* LockPower = (2 * Strength) + (.5 * Passion) */
    return (this->Strength * 2) + (this->Passion / 2);
}

int32 UCharacterStats::getAPReductionPower()
{
    /* APReducPower = (Wisdom * 3) + Intelligence */
    return (this->Wisdom * 3) + this->Intelligence;
}

int32 UCharacterStats::getAPReductionResistance()
{
    /* APReducResist = (Wisdom * 3) + Passion */
    return (this->Wisdom * 3) + this->Passion;
}

int32 UCharacterStats::getMPReductionPower()
{
    /* MPReducPower = (Wisdom * 3) + Dexterity */
    return (this->Wisdom * 3) + this->Dexterity;
}

int32 UCharacterStats::getMPReductionResistance()
{
    /* MPReducResist = (Wisdom * 3) + Agility */
    return (this->Wisdom * 3) + this->Agility;
}

int32 UCharacterStats::getCarryCapactity()
{
    /* Capacity = (Strength * 10) */
    return this->Strength * 10;
}

UCharacterStats * UCharacterStats::copyOf()
{
    return new UCharacterStats(
        Strength, Agility, Dexterity, Intelligence, Passion, Wisdom, Vitality
    );
}

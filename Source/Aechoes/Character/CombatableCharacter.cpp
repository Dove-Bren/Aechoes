// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "CombatableCharacter.h"

ACombatableCharacter::ACombatableCharacter(const class FObjectInitializer& ObjectInitializer)
{
    
    //this->stats = NewObject<UCharacterStats>();
	this->stats = CreateDefaultSubobject<UCharacterStats>(TEXT("Stats"));
	if (this->stats == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Created stats are null!-----------------------"));
	}
    this->maxAP = ACombatableCharacter::DEFAULT_MAXAP;
    this->maxMP = ACombatableCharacter::DEFAULT_MAXMP;

    this->AP = this->maxAP;
    this->MP = this->maxMP;
}

ACombatableCharacter::~ACombatableCharacter()
{
    //delete stats;
}

uint8 ACombatableCharacter::getAP()
{
    return this->AP;
}

uint8 ACombatableCharacter::getMaxAP()
{
    return this->maxAP;
}

uint8 ACombatableCharacter::getMP()
{
    return this->MP;
}

uint8 ACombatableCharacter::getMaxMP()
{
    return this->maxMP;
}

uint8 ACombatableCharacter::addAP(uint8 amount)
{
    this->AP += amount;
    if (this->AP < 0)
        this->AP = 0;
    else if (this->AP > this->maxAP)
        this->AP = this->maxAP;

    return this->AP;
}

uint8 ACombatableCharacter::addMP(uint8 amount)
{
    this->MP += amount;
    if (this->MP < 0)
        this->MP = 0;
    else if (this->MP > this->maxMP)
        this->MP = this->maxMP;

    return this->MP;
}

void ACombatableCharacter::setMaxAP(uint8 amount)
{
    this->maxAP = amount;
}

void ACombatableCharacter::setMaxMP(uint8 amount)
{
    this->maxMP = amount;
}

void ACombatableCharacter::setAP(uint8 amount)
{
    this->AP = amount;
}

void ACombatableCharacter::setMP(uint8 amount)
{
    this->MP = amount;
}

UCharacterStats * ACombatableCharacter::getStats()
{
    return this->stats->copyOf();
}

void ACombatableCharacter::AddStrength()
{
	this->stats->Strength++;

}



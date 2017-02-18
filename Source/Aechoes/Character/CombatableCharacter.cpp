// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "CombatableCharacter.h"

ACombatableCharacter::ACombatableCharacter(const class FObjectInitializer& ObjectInitializer)
	: ALivingCharacter::ALivingCharacter(ObjectInitializer)
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

	this->bIsAttacking = false;

	this->lrid = CreateDefaultSubobject<ULrid>(TEXT("Movement Grid"));
	this->loslrid = CreateDefaultSubobject<ULosLrid>(TEXT("LoS Grid"));

	this->Default_Close_Combat = CreateDefaultSubobject<UAttackSimple>(TEXT("Base Melee Attack"))
		->name(FName("Close Combat"))
		->desc(NSLOCTEXT("COMBAT", "DEFAULT_MELEE", "Perform a regular melee hit"))
		->range(1)
		->add(DamageType::NEUTRAL, 1, 4);
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

bool ACombatableCharacter::isCommandReady()
{
	if (!Super::isCommandReady())
		return false;

	return !bIsAttacking;
}

void ACombatableCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (lrid == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid lrid pointer!"));
	}
	else {
		lrid->SetOwner(this);
		lrid->SetMaxLength(getMP());
		lrid->Update();
	}
}

ULrid *ACombatableCharacter::GetLrid()
{
	return lrid;
}

void ACombatableCharacter::UpdateLrid()
{
	if (lrid != nullptr)
		lrid->Update();
}

ULosLrid *ACombatableCharacter::GetLosLrid()
{
	return loslrid;
}

void ACombatableCharacter::UpdateLosLrid()
{
	if (loslrid != nullptr)
		loslrid->Update();
}

void ACombatableCharacter::SetEffectiveLocation(FVector in, bool rebuild)
{
	Super::SetEffectiveLocation(in, rebuild);

	if (rebuild && lrid != nullptr) {
		lrid->SetMaxLength(getMP());
		lrid->Update();
	}
}

TArray<FDamageVector> ACombatableCharacter::AdjustDamages(TArray<FDamageVector> const InputVectors)
{
	TArray<FDamageVector> out = InputVectors;

	//TODO

	return out;
}

TArray<FDamageVector> ACombatableCharacter::AugmentDamages(TArray<FDamageVector> const InputVectors)
{
	TArray<FDamageVector> out = InputVectors;

	//TODO

	return out;
}

void ACombatableCharacter::TurnTick()
{
	if (BattleModifiers.Num() == 0)
		return;

	int index = 0;
	while (index < BattleModifiers.Num()) {
		if (BattleModifiers[index].TurnTick()) {
			BattleModifiers.RemoveAt(index);
			continue;
		}
		else {
			index++; //go to next index
		}
	}
}

void ACombatableCharacter::AddModifier(FDamageModifier mod)
{
	BattleModifiers.Add(mod);
}

void ACombatableCharacter::ClearModifiers()
{
	BattleModifiers.Empty();
}
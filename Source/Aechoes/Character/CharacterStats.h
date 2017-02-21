// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "../Combat/Mechanics/DamageVector.h"
#include "CharacterStats.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API UCharacterStats : public UActorComponent
{
    GENERATED_BODY()
    
public:

    /** Governs Neutral Damage **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Strength;

    /** Governs Air Damage **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Agility;

    /** Governs Earth Damage **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Dexterity;

    /** Governs Fire Damage **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Intelligence;

    /** Governs Water Damage **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Passion;

    /** Governs experience **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Wisdom;

    /** Governs Health **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    int32 Vitality;

    UCharacterStats(const class FObjectInitializer& ObjectInitializer);

    //UCharacterStats(int32 strength, int32 agility, int32 dexterity, int32 intel,
    //               int32 passion, int32 wisdom, int32 vit);


    /*******************************
     * Derived Stat Definitions   *
     *******************************/

    /** 
     * Calculates effective Initiative, from stats alone. This doens't include
     * any initiative gained from equipment bonuses.
     * Initiative is used to determine combat order at start of combat
     * @return initiative based only on stats.
     **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getInitiative();

    /** 
     * Calculates effective Fortune from stats alone.
     * Fortune is used when making rolls for loot.
     * @return fortune based only on stats.
     **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getFortune();

    /**
    * Calculates maximum Health based on stats alone.
    * This value is the unmodified maximum health of the character.
    * @return health based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getHealth();

    /**
    * Calculates and returns power to make dodges.
    * Dodge power is used when attempted to disengage an enemy, and is checked
    * against the enemy's lock power.
    * @return dodge power based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getDodgePower();

    /**
    * Returns power to prevent dodges
    * Lock power is checked when an enemy is attempted to disengage
    * @return lock power based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getLockPower();

    /**
    * Calculates power to reduce AP.
    * AP Reduc Power is used when rolling to reduce a character's AP. It is
    * checked against the enemy's AP Reduc Resistance.
    * @return ap reduction power based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getAPReductionPower();

    /**
    * Calculates power to avoid AP reduction.
    * AP Reduc Resistance is used when rolling to prevent AP loss from
    * another character.
    * @return ap reduction resistance based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getAPReductionResistance();

    /**
    * Calculates power to reduce MP.
    * Just like AP reduc power, but with MP
    * @return mp reduction power based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getMPReductionPower();

    /**
    * Calculates power to avoid MP reduction.
    * This is just like AP Reduction Resistance, but with MP
    * @return mp reduction resistance based only on stats.
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getMPReductionResistance();

    /**
    * Calculates this character's carry capacity from their stats. The
    * produced value does not consider character equipment, etc, and is
    * expected only to serve as a base amount.
    * @return The base amount of carrying capacity
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    int32 getCarryCapactity();


    /*******************************
    *    Modifier Definitions      *
    *******************************/
    
    float getModifier(DamageType type)
    {
        switch (type) {
            case DamageType::AIR:
                return 1.0 + ((float) this->Agility / 100.0f);
            case DamageType::EARTH :
                return 1.0 + ((float) this->Dexterity / 100.0f);
            case DamageType::WATER:
                return 1.0 + ((float) this->Passion / 100.0f);
            case DamageType::FIRE:
                return 1.0 + ((float) this->Intelligence / 100.0f);
            case DamageType::NEUTRAL:
                return 1.0 + ((float) this->Strength / 100.0f);
            default:
                return 0.0;
        }
    }



    /****************************
     * Helper Functions
     ****************************/

    UCharacterStats *copyOf();
};

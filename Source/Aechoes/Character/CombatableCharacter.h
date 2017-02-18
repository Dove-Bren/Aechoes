// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LivingCharacter.h"
#include "CharacterStats.h"
#include "../Combat/DamageModifier.h"
#include "../Combat/Attack.h"
#include "../Combat/AttackSimple.h"
#include "../World/Navigation/Lrid.h"
#include "../World/Navigation/LosLrid.h"
#include "CombatableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API ACombatableCharacter : public ALivingCharacter
{
    GENERATED_BODY()

private:
    static uint8 const DEFAULT_MAXAP = 6;
    static uint8 const DEFAULT_MAXMP = 3;
    
protected:

    /**
     * Character Stats structure. Core stat reference! Be careful to hand out
     * copies when allowing other things to reference them
     **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	UCharacterStats *stats;// = NewObject<UCharacterStats>();

    /** Maximum AP **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 maxAP;

    /** Current AP **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 AP;

    /** Maximum MP **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 maxMP;

    /** Current MP **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    uint8 MP;

	/** Whether or not we are currently attacking **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	bool bIsAttacking;

	/** Temp Lrid Handle **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Movement)
	ULrid *lrid;

	/** Temp Action Lrid Handle **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Movement)
	ULosLrid *loslrid;

	/** Collection of modifiers **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
	TArray<FDamageModifier> BattleModifiers;

	/** All learnt skills and spells **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
	TArray<TScriptInterface<IAttack>> Attacks;
    


public:

	UAttackSimple const *DEFAULT_CLOSE_COMBAT
		= UAttackSimple(FName("Close Combat"), NSLOCTEXT("COMBAT", "DEFAULT_MELEE", "Perform a regular melee hit"), 1)
			.add(DamageType::NEUTRAL, 1, 4);
    
    ACombatableCharacter(const class FObjectInitializer& ObjectInitializer);

    ~ACombatableCharacter();

    /** 
     * Returns the current amount of available AP 
     * @return Current AP
     **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 getAP();

    /**
    * Returns the maximum amount of AP
    * @return Maximum AP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 getMaxAP();

    /**
    * Returns the current amount of available MP
    * @return Current MP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 getMP();

    /**
    * Returns the maximum amount of MP
    * @return Maximum MP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 getMaxMP();

    /**
    * Adds the amount of available AP. This can be negative.
    * @return The amount of AP available after the addition
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 addAP(uint8 amount);

    /**
    * Adds the amount of available MP. This can be negative.
    * @return The amount of MP available after the addition
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    uint8 addMP(uint8 amount);

    /**
    * Sets the maximum number of AP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    void setMaxAP(uint8 amount);

    /**
    * Sets the maximum number of MP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    void setMaxMP(uint8 amount);

    /**
    * Sets the currently available AP
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    void setAP(uint8 amount);

    /**
    * Sets the MP that are currently available for use
    **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    void setMP(uint8 amount);

    /**
     * Returns a workable copy of this character's stats
     * @return a COPY of this character's stats
     **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    UCharacterStats *getStats();

	/** TEST TEMP **/
	UFUNCTION(BlueprintCallable, Category = Combat)
	void AddStrength();
	
	// Get this character's active LRid 
	ULrid *GetLrid();

	// Call this character's Lrid for Update
	UFUNCTION(BlueprintCallable, Category = Combat)
	void UpdateLrid();

	// Get this character's active LRid 
	ULosLrid *GetLosLrid();

	// Call this character's Lrid for Update
	UFUNCTION(BlueprintCallable, Category = Combat)
	void UpdateLosLrid();
    
	UFUNCTION(BlueprintCallable, Category = Living)
	bool isCommandReady() override;

	void BeginPlay() override;

	virtual void SetEffectiveLocation(FVector in, bool rebuildLrid) override;

	virtual TArray<FDamageVector> AdjustDamages(TArray<FDamageVector> const InputVectors) override;

	/**
	 * Takes the provided vectors and applies augmentations based on
	 * this character's governing stats.
	 * @param The vectors to apply augmentations to
	 * @return The augmented vectors
	 **/
	virtual TArray<FDamageVector> AugmentDamages(TArray<FDamageVector> const InputVectors);

	virtual void AddModifier(FDamageModifier mod);

	virtual void ClearModifiers();

	virtual void TurnTick();
};

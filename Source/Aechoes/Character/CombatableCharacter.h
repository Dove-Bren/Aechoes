// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LivingCharacter.h"
#include "CharacterStats.h"
#include "../World/Navigation/Lrid.h"
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
    


public:
    
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
    
	UFUNCTION(BlueprintCallable, Category = Living)
	bool isCommandReady() override;

	void BeginPlay() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AechoesCharacter.h"
#include "LivingCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API ALivingCharacter : public AAechoesCharacter
{
	GENERATED_BODY()

	/** Default Max Health **/
	static int32 const DEFAULT_MAXHEALTH = 20;

	/** Default Health Regeneration Rate **/
	static int32 const DEFAULT_HEALTHREGEN = 5;

protected:

	/** Health **/
	UPROPERTY(BlueprintReadOnly, Category = Living)
	int health;

	/** Max Health **/
	UPROPERTY(BlueprintReadOnly, Category = Living)
	int maxHealth;

	/** Health Regeneration Rate outside of Combat **/
	UPROPERTY(BlueprintReadOnly, Category = Living)
	int healthRegenRate;

	/** Perform death-time actions **/
	UFUNCTION(BlueprintNativeEvent, Category = Living)
	void die();

	virtual void die_Implementation();


public:
	
	ALivingCharacter();

	ALivingCharacter(int maxHealth);

	/** Fetch the amount of health remaining **/
	UFUNCTION(BlueprintCallable, Category = Living)
	int getHealth();

	/** Fetch the maximum amount of health **/
	UFUNCTION(BlueprintCallable, Category = Living)
	int getMaxHealth();

	/** Deals damage to the character
	 * @param amount The amount of damage done
	 **/
	UFUNCTION(BlueprintCallable, Category = Living)
	void damage(int amount);

	/** Marks the character as dead */
	UFUNCTION(BlueprintCallable, Category = Living)
	void kill();

	/** Checks and returns whether the character is dead
	 * @return True when the character is dead; false otherwise
	 **/
	UFUNCTION(BlueprintCallable, Category = Living)
	bool isDead();

	/** Fetches this character's health regen rate
	* @return The regen rate
	**/
	UFUNCTION(BlueprintCallable, Category = Living)
	int32 getHealthRegen();

	/** Fetches this character's health regen rate
	* @return The regen rate
	**/
	UFUNCTION(BlueprintCallable, Category = Living)
	void setHealthRegen(int32 regenRate);

	void Tick(float delta);

};

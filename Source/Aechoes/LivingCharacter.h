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
	static int const DEFAULT_MAXHEALTH = 20;

protected:

	/** Health **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Living)
	int health;

	/** Max Health **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Living)
	int maxHealth;

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
};

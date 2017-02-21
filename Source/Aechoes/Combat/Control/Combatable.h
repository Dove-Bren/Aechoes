// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combatable.generated.h"

class ACombatableCharacter;

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UCombatable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class AECHOES_API ICombatable
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/** Called when character is entering fight. This is
	 * before the battle has begun, and during placement phase **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void EnterFight();

	/** Called when the fight begins **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void BeginFight();

	/** Called when the fight is over **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void EndFight();

	/** Called just before moving the character back to the map **/
	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
	void ExitFight();

	///** Called when character is entering fight. This is
	//* before the battle has begun, and during placement phase **/
	//void EnterFight();

	///** Called when the fight begins **/
	//void BeginFight();

	///** Called when the fight is over **/
	//void EndFight();

	///** Called just before moving the character back to the map **/
	//void ExitFight();
   
	
};

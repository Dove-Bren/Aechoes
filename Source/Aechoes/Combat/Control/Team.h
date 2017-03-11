// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Character/CombatableCharacter.h"
#include "Team.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AECHOES_API FTeam
{
	GENERATED_BODY()

protected:

	// Collection of characters on the team
	TSet<ACombatableCharacter *> Members;

public:

	FTeam();

	/**
	 * Add a member to this team
	 * @param newMember the new member
	 */
	void AddMember(ACombatableCharacter *newMember);

	/**
	 * Try to check whether the given member is part of this team
	 */
	bool IsMember(ACombatableCharacter *member);
	
	   
	
};

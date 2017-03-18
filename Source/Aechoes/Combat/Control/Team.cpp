// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "Team.h"

FTeam::FTeam()
{
	;
}

/**
* Add a member to this team
* @param newMember the new member
*/
void FTeam::AddMember(ACombatableCharacter *newMember)
{
	Members.Add(newMember);
}

/**
* Try to check whether the given member is part of this team
*/
bool FTeam::IsMember(ACombatableCharacter *member)
{
  return Members.Contains(member);
}

const TSet<ACombatableCharacter *> FTeam::GetMemberList()
{
  return Members;
}


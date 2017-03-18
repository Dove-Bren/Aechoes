// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "CombatClock.h"

UCombatClock::UCombatClock()
{
  InInterval = false;
  TimeLeft = 0.0f;
}


void UCombatClock::InitParticipants(TArray<ACombatableCharacter *> &Participants)
{
  Lineup = Participants;
}

/**
* Removes a character from the lineup. After being removed, the character
* will not be prompted for a turn again. Expected to be called on death.
* @param soughtMember The member to attempt to remove
*/
void UCombatClock::RemoveCharacter(ACombatableCharacter *soughtMember)
{
  Lineup.Remove(soughtMember);
}

/**
* Returns an array with the current turn lineup.
* @return TArray with characters ordered to turn order
*/
const TArray<ACombatableCharacter *> &UCombatClock::GetLineup()
{
  return Lineup;
}

ACombatableCharacter * UCombatClock::GetActive()
{
  return Lineup[TurnIndex];
}

float UCombatClock::GetTimeLeft()
{
  return this->TimeLeft;
}

void UCombatClock::TickComponent(float DeltaTime, enum ELevelTick TickType,
  FActorComponentTickFunction * ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


  TimeLeft -= DeltaTime;
  if (TimeLeft < 0) {

    //if not in interval, go to interval and wait
    if (!InInterval) {
      InInterval = true;
      OnTurnEnd.Broadcast(GetActive());
      TimeLeft = UCombatClock::WAIT_TIME;
    }
    else {
      InInterval = false;
      TurnIndex++;
      if (TurnIndex > Lineup.Num())
        TurnIndex = 0;

      TimeLeft = UCombatClock::TURN_TIME;
      OnTurnStart.Broadcast(GetActive());
    }

  }
}
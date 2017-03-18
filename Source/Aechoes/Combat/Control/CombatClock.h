// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "../../Character/CombatableCharacter.h"
#include "CombatClock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnDelegate, ACombatableCharacter *, Character);

/**
 * 
 */
UCLASS()
class AECHOES_API UCombatClock : public UActorComponent
{
  GENERATED_BODY()

protected:

  UPROPERTY(BlueprintReadOnly, Category = Turns)
  FTurnDelegate OnTurnStart;

  UPROPERTY(BlueprintReadOnly, Category = Turns)
  FTurnDelegate OnTurnEnd;

	// List of turns
  UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Turns)
	TArray<ACombatableCharacter *> Lineup;

  // Current turn position
  UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Turns)
  int32 TurnIndex;

  // Time Left in Current Turn - In Seconds
  UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Turns)
  float TimeLeft;

  // Are we in turn interval -- time between turns
  UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Turns)
  bool InInterval;

  /**** Constants for Combat  ****/

  //Maximum time given for a turn
  int32 static const TURN_TIME = 30;

  //Time to wait before starting next turn
  int32 static const WAIT_TIME = 1;

public:

  UCombatClock();

  /**
   * Takes participants and forms turn list.
   * Throws out any old information that may be present.
   * @param Participants a set of characters to create turn list out of
   **/
  UFUNCTION(BlueprintCallable, Category = Turns)
  void InitParticipants(TArray<ACombatableCharacter *> &Participants);

	/**
	 * Removes a character from the lineup. After being removed, the character
   * will not be prompted for a turn again. Expected to be called on death.
	 * @param soughtMember The member to attempt to remove
	 */
  UFUNCTION(BlueprintCallable, Category = Turns)
	void RemoveCharacter(ACombatableCharacter *soughtMember);

  /**
   * Returns an array with the current turn lineup.
   * @return TArray with characters ordered to turn order
   */
  UFUNCTION(BlueprintCallable, Category = Turns)
  const TArray<ACombatableCharacter *> &GetLineup();

  /**
  * Return the current participant. That is, returns the participant whose
  * turn it is.
  * @return The active participant. During the interval period (right after
  *         a character's turn ends), will point to the last participant
  */
  UFUNCTION(BlueprintCallable, Category = Turns)
  ACombatableCharacter *GetActive();

  /**
  * Return the amount of time left in the current turn.
  * @return Time left. Returns -1 during interval period
  */
  UFUNCTION(BlueprintCallable, Category = Turns)
  float GetTimeLeft();

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
    FActorComponentTickFunction * ThisTickFunction) override;
	
	   
	
};

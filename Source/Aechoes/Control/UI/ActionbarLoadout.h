#pragma once

#include "ActionbarLoadout.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FActionbarLoadout
{
	GENERATED_USTRUCT_BODY()

	FActionbarLoadout();

	static uint8 const MAX_SLOT = 20;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat | Control")
	TArray<int32> SlotArray;

	/**
	 * Fetches the ID at the given index.
	 * If it hasn't been set, will return 0. If the index is invalid,
	 * will return -1
	 **/
	int32 GetID(uint8 index);

	/**
	 * Sets the id at the given index.
	 * Does nothing if index is invalid
	 **/
	void SetID(uint8 index, int32 id);

};
#pragma once

#include "AttackRecord.h"
#include "AttackRegistry.generated.h"

//UENUM(BlueprintType)
//enum class DamageCheckType : uint8
//{
//	ON_ATTACK,
//	ON_DEFEND,
//	ALWAYS
//};
//
//UENUM(BlueprintType)
//enum class DamagePass : uint8
//{
//	CONSTANT_PASS,
//	SCALE_PASS,
//	FINAL_PASS
//};

/**
 * Registry class that stores information about attacks.
 **/
UCLASS()
class UAttackRegistry : public UObject
{
    GENERATED_BODY()

public:

	UAttackRegistry();

protected:

	/** Collection of active records **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	TMap<int32, FAttackRecord> Records;

	/** Internal number cache used when finding valid keys **/
	int32 LastAvailKey;


public:

	/** Find an available attack Id thats not currently associated with anything. **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	int32 FindUnusedKey();

	/** Lookup an attack record for the given ID. Returns an
	 *  empty struct when it doesn't exist! Check before using! **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	FAttackRecord Lookup(int32 key);

	/** Check whether the given ID has an active record **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	bool HasEntry(int32 key);

	/** Store (Overwrite!) the given record at the given key. **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	void Store(int32 key, FAttackRecord record);



};
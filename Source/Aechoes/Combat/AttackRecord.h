#pragma once

#include "Attack.h"
#include "AttackRecord.generated.h"

/**
 * Attack record, with all the information stored on the attack
 **/
USTRUCT()
struct FAttackRecord
{
    GENERATED_USTRUCT_BODY()

protected:

	/** Actual attack reference **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	TScriptInterface<IAttack> Attack;

	/** Texture used as button overlay **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
	UTexture2D *Icon;



public:

	FAttackRecord();

	static FAttackRecord Make(TScriptInterface<IAttack> AttackRef, UTexture2D *IconRef);

	UTexture2D *GetIcon();

	TScriptInterface<IAttack> GetAttack();

};
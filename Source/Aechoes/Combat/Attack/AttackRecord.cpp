

#include "Aechoes.h"
#include "AttackRecord.h"

FAttackRecord::FAttackRecord()
{
	;
}


FAttackRecord FAttackRecord::Make(TScriptInterface<IAttack> AttackRef, UTexture2D *IconRef)
{
	FAttackRecord rec;

	rec.Icon = IconRef;
	rec.Attack = AttackRef;

	return rec;
}

UTexture2D *FAttackRecord::GetIcon()
{
	return Icon;
}

TScriptInterface<IAttack> FAttackRecord::GetAttack()
{
	return Attack;
}
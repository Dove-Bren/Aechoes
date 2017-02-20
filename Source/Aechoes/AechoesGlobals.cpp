// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "Engine/GameInstance.h" 
#include "AechoesGlobals.h"

UAechoesGlobals::UAechoesGlobals()
{
	AttackRegistry = CreateDefaultSubobject<UAttackRegistry>(TEXT("Attack Registry"));
}

UAechoesGlobals *UAechoesGlobals::Fetch(UWorld *ref)
{

	if (!ref)
		ref = GEngine->GetWorld();

	if (ref)
		return Cast<UAechoesGlobals>(ref->GetGameInstance());

	return nullptr;
}

UWorldGrid *UAechoesGlobals::FetchGrid(UWorld *ref)
{
	UAechoesGlobals *glob = UAechoesGlobals::Fetch(ref);
	if (!glob)
		return nullptr;

	return glob->GetGrid();
}

void UAechoesGlobals::SetGrid(UWorldGrid *grid)
{
	WorldGrid = grid;
}

UWorldGrid *UAechoesGlobals::GetGrid()
{
	return WorldGrid;
}

UAttackRegistry *UAechoesGlobals::GetAttackRegistry()
{
	return AttackRegistry;
}

FActionbarLoadout UAechoesGlobals::GetABarLoadout(ACombatableCharacter* key)
{
	FActionbarLoadout * ref = ALoadoutMap.Find(key);
	if (ref == nullptr)
		return FActionbarLoadout();

	return *ref;
}

/** Set the ABar loadout for the given character **/
void UAechoesGlobals::SetABarLoadout(ACombatableCharacter* key, FActionbarLoadout loadout)
{
	ALoadoutMap.Add(key, loadout);
}

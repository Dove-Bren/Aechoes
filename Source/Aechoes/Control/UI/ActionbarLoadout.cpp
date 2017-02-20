

#include "Aechoes.h"
#include "ActionbarLoadout.h"

FActionbarLoadout::FActionbarLoadout()
{
	SlotArray.SetNum(FActionbarLoadout::MAX_SLOT);
}

int32 FActionbarLoadout::GetID(uint8 index)
{
	if (index > FActionbarLoadout::MAX_SLOT)
		return -1;

	return SlotArray[index];
}

void FActionbarLoadout::SetID(uint8 index, int32 id)
{
	if (index > FActionbarLoadout::MAX_SLOT)
		return;

	SlotArray[index] = id;
}
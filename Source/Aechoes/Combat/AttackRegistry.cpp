

#include "Aechoes.h"
#include "AttackRegistry.h"

UAttackRegistry::UAttackRegistry()
{
	;
}

/** Find an available attack Id thats not currently associated with anything. **/
int32 UAttackRegistry::FindUnusedKey()
{
	int32 start = LastAvailKey++;
	while (start != LastAvailKey //stop once we circle all values
		     && HasEntry(LastAvailKey))
		LastAvailKey++;

	return LastAvailKey; //even if it's invalid, all we can do is return it
}


/** Lookup an attack record for the given ID. Returns nullptr
*  when no match exists **/
FAttackRecord UAttackRegistry::Lookup(int32 key)
{
	
	FAttackRecord *rec = Records.Find(key);
	if (rec == nullptr)
		return FAttackRecord();

	return *rec;
}

/** Check whether the given ID has an active record **/
bool UAttackRegistry::HasEntry(int32 key)
{
	return (nullptr == Records.Find(key));
}

/** Store (Overwrite!) the given record at the given key. **/
void UAttackRegistry::Store(int32 key, FAttackRecord record)
{
	Records.Add(key, record);
}


#include "Aechoes.h"
#include "DamageModifier.h"

//FDamageModifier::FDamageModifier()
//{
//	ApplyType = DamageCheckType::ON_ATTACK;
//	DamageFilter = DamageType::NONE;
//}
//
//FDamageModifier::FDamageModifier(float scale, int32 offset, DamageType type, DamageCheckType applyType)
//{
//	Offset = offset;
//	Scale = scale;
//	ApplyType = applyType;
//	DamageFilter = type;
//};

bool FDamageModifier::CanApply(FDamageVector const & inVector, bool isAttack)
{
	if ((isAttack && ApplyType == DamageCheckType::ON_DEFEND)
		|| (!isAttack && ApplyType == DamageCheckType::ON_ATTACK)) {
		return false;
	}

	return DamageFilter == DamageType::ALL
		|| DamageFilter == inVector.damageType;
}

void FDamageModifier::Apply(FDamageVector & input, DamagePass passType)
{
	//simple modifiers only have scale and constant passes
	if (passType == DamagePass::CONSTANT_PASS)
		input.amount += Offset;
	else if (passType == DamagePass::SCALE_PASS)
		input.amount *= Scale;
	

	//else do nothing
}

bool FDamageModifier::TurnTick()
{
	//simply update turns-left, and get self removed when turns are over
	TurnsLeft--;

	return (TurnsLeft <= 0);
}

#pragma once

#include "Spells/SpellBase.h"
#include "SpiritDropSpell.generated.h"

UCLASS()
class OTHERLAND_API USpiritDropSpell : public USpellBase
{
	GENERATED_BODY()

public:

	USpiritDropSpell();
	~USpiritDropSpell();

	void Behaviour();
	void PlaySound();
};

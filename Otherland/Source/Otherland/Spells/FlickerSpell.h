#pragma once

#include "Spells/SpellBase.h"
#include "FlickerSpell.generated.h"

UCLASS()
class OTHERLAND_API UFlickerSpell : public USpellBase
{
	GENERATED_BODY()

public:

	UFlickerSpell();
	~UFlickerSpell();

	void Behaviour();
	void Finish();
	void PlaySound();
};

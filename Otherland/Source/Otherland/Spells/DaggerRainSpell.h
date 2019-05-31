#pragma once

#include "Spells/SpellBase.h"
#include "DaggerRainSpell.generated.h"

UCLASS()
class OTHERLAND_API UDaggerRainSpell : public USpellBase
{
	GENERATED_BODY()

public:

	UDaggerRainSpell();
	~UDaggerRainSpell();

	void Behaviour();
	void Finish();
	void PlaySound();
};

#pragma once

#include "Spells/SpellBase.h"
#include "ShadowstepSpell.generated.h"

UCLASS()
class OTHERLAND_API UShadowstepSpell : public USpellBase
{
	GENERATED_BODY()

public:

	UShadowstepSpell();
	~UShadowstepSpell();

	void Behaviour();
	void Finish();
};



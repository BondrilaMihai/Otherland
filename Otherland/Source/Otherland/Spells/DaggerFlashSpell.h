#pragma once

#include "Spells/SpellBase.h"
#include "DaggerFlashSpell.generated.h"

UCLASS()
class OTHERLAND_API UDaggerFlashSpell : public USpellBase
{
	GENERATED_BODY()

public:

	UDaggerFlashSpell();
	~UDaggerFlashSpell();

	void Behaviour();
	void Finish();
	void PlaySound();
};

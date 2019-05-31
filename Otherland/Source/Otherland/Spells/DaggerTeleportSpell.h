#pragma once

#include "Spells/SpellBase.h"
#include "DaggerTeleportSpell.generated.h"

UCLASS()
class OTHERLAND_API UDaggerTeleportSpell : public USpellBase
{
	GENERATED_BODY()

public:

	UDaggerTeleportSpell();
	~UDaggerTeleportSpell();

	void Behaviour();
	void Finish();
	void PlaySound();
};

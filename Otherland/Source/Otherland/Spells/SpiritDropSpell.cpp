#include "SpiritDropSpell.h"

USpiritDropSpell::USpiritDropSpell()
{
}


USpiritDropSpell::~USpiritDropSpell()
{
}

void USpiritDropSpell::Behaviour()
{
	getCaster()->LaunchCharacter(FVector(0.0f, 0.0f, -2000.0f), false, false);
}
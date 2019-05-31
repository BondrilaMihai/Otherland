#include "SpiritDropSpell.h"

USpiritDropSpell::USpiritDropSpell()
{
}


USpiritDropSpell::~USpiritDropSpell()
{
}

void USpiritDropSpell::Behaviour()
{
	getCaster()->setCharacterState(ECharacterStates::State_SpiritDrop);
	getCaster()->LaunchCharacter(FVector(0.0f, 0.0f, -2000.0f), false, false);
}

void USpiritDropSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Spirit_Drop_Dash_Cue.Spirit_Drop_Dash_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}
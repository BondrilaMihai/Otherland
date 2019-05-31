#include "DaggerRainSpell.h"
#include "Enemies/AssassinBoss.h"

UDaggerRainSpell::UDaggerRainSpell()
{
}


UDaggerRainSpell::~UDaggerRainSpell()
{
}

void UDaggerRainSpell::Behaviour()
{
	getCaster()->setCharacterState(ECharacterStates::State_DaggerRain);

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UDaggerRainSpell::Finish, 2, false);
}

void UDaggerRainSpell::Finish()
{
	getCaster()->getSpellSoundComponent()->Stop();
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

void UDaggerRainSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Throw_Loop_Cue.Throw_Loop_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}
#include "DaggerFlashSpell.h"
#include "Enemies/AssassinBoss.h"

UDaggerFlashSpell::UDaggerFlashSpell()
{
}


UDaggerFlashSpell::~UDaggerFlashSpell()
{
}

void UDaggerFlashSpell::Behaviour()
{
	getCaster()->setCharacterState(ECharacterStates::State_DaggerFlash);

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UDaggerFlashSpell::Finish, 1, false);
}

void UDaggerFlashSpell::Finish()
{
	getCaster()->getSpellSoundComponent()->Stop();
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

void UDaggerFlashSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Dagger_Flash_Cue.Dagger_Flash_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}
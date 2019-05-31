#include "DaggerTeleportSpell.h"
#include "Enemies/AssassinBoss.h"

UDaggerTeleportSpell::UDaggerTeleportSpell()
{
}


UDaggerTeleportSpell::~UDaggerTeleportSpell()
{
}

void UDaggerTeleportSpell::Behaviour()
{
	getCaster()->setCharacterState(ECharacterStates::State_DaggerTp);

	static_cast<AAssassinBoss*>(getCaster())->setSprite(Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Game/Sprites/AssassinsSprites/Boss/DaggerTp/A_DaggerTp.A_DaggerTp'"))));

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UDaggerTeleportSpell::Finish, 1, false);
}

void UDaggerTeleportSpell::Finish()
{
	getCaster()->getSpellSoundComponent()->Stop();
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

void UDaggerTeleportSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Throw_Cue.Throw_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}
#include "FlickerSpell.h"
#include "Enemies/AssassinBoss.h"

UFlickerSpell::UFlickerSpell()
{
}


UFlickerSpell::~UFlickerSpell()
{
}

void UFlickerSpell::Behaviour()
{
	getCaster()->setCharacterState(ECharacterStates::State_Flicker);

	//static_cast<AAssassinBoss*>(getCaster())->setSprite(Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Shadowstep_Start_Cue.Shadowstep_Start_Cue'"))));

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UFlickerSpell::Finish, 1, false);

	if (static_cast<AAssassinBoss*>(getCaster())->IsMovingRight())
		getCaster()->GetCharacterMovement()->AddImpulse(FVector(300.0f, 0.0f, 0.0f));

	else
		getCaster()->GetCharacterMovement()->AddImpulse(FVector(-300.0f, 0.0f, 0.0f));
}

void UFlickerSpell::Finish()
{
	getCaster()->getSpellSoundComponent()->Stop();
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

void UFlickerSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Flicker_Cue.Flicker_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}
#include "ShadowstepSpell.h"
#include "TimerManager.h"

UShadowstepSpell::UShadowstepSpell()
{
}


UShadowstepSpell::~UShadowstepSpell()
{
}

void UShadowstepSpell::Behaviour()
{
	getCaster()->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	getCaster()->setCharacterState(ECharacterStates::State_Shadowstep);

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UShadowstepSpell::Finish, 4, false);
}

/** Apelata automat de Behaviour() dupa ce durata abilitatii se incheie */
void UShadowstepSpell::Finish()
{
	getCaster()->getSpellSoundComponent()->Stop();
	getCaster()->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

void UShadowstepSpell::PlaySound()
{
	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Shadowstep_Start_Cue.Shadowstep_Start_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();

	getCaster()->getSpellSoundComponent()->SetSound(Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Game/Audio/Spells/Shadowstep_Active_Cue.Shadowstep_Active_Cue'"))));
	getCaster()->getSpellSoundComponent()->Play();
}

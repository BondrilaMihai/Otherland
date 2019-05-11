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
	getCaster()->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	getCaster()->setCharacterState(ECharacterStates::State_Idle);
}

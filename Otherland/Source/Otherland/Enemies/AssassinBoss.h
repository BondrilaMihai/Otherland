// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/MyCharacter.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Paper2D/Classes/PaperFlipbook.h"
#include "Spells/ShadowstepSpell.h"
#include "Spells/FlickerSpell.h"
#include "Spells/DaggerTeleportSpell.h"
#include "Spells/DaggerFlashSpell.h"
#include "Spells/DaggerRainSpell.h"
#include "AssassinBoss.generated.h"

const float SHORT_DISTANCE = 150.0f;
const float MEDIUM_DISTANCE = 400.0f;

UCLASS()
class OTHERLAND_API AAssassinBoss : public AMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAssassinBoss();
	~AAssassinBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	friend class AssassinBossDecisionThread;

	class AssassinBossDecisionThread* _decisionThread;

	/* ABILITATI */

	UPROPERTY()
		UShadowstepSpell* _shadowstep;

	UPROPERTY()
		UFlickerSpell* _flicker;

	UPROPERTY()
		UDaggerTeleportSpell* _daggTp;

	UPROPERTY()
		UDaggerFlashSpell* _daggFlash;

	UPROPERTY()
		UDaggerRainSpell* _daggRain;

	/* COMPONENTE */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UPaperFlipbookComponent* _sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* _daggTpArrow;

public:

	bool IsMovingRight();

	/* GETTERS & SETTERS */

	UPaperFlipbookComponent* getSprite() const;
	void setSprite(UPaperFlipbook* sprite);

	/* ABILITATI */

	void InitSpells();

	/* FUNCTII PENTRU AI */

	/** Distanta fata de player, returneaza 0 daca player-ul este aproape, 1 daca player-ul este la o distanta medie si 2 daca player-ul este departe */
	uint8 checkPlayerDistance();

	void JumpBack(bool isFacingRight);
	void WalkBack(bool isFacingRight);
	void MeleeAttack();
	void RangedAttack();

	/** Verifica daca o abilitate poate fi folosita */
	bool SpellReady(const USpellBase& spell);
};

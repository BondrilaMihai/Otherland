// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Character/MyCharacter.h"
#include "SpellBase.generated.h"

/* Clasa de baza pentru abilitati, cand faceti o abilitate noua o derivati din clasa asta */

UCLASS()
class OTHERLAND_API USpellBase : public UObject
{
	GENERATED_BODY()
	
	uint8 _cooldown;
	uint8 _cost;
	uint8 _damage;

	/** Daca poate fi folosita abilitatea */
	bool _canBeCast;

	/** Numele legat de ex "SpellOne" */
	FString _name;

	/** Cine a folosit abilitatea, in cazul in care si un inamic poate folosi abilitatea si nu doar player-ul */
	UPROPERTY()
		AMyCharacter* _caster;

public:

	USpellBase();
	~USpellBase();

	/** Seteaza valorile, folositi dupa ce apelati constructor-ul */
	void init(uint8 cooldown, uint8 cost, FString name, bool canBeCast, AMyCharacter* caster, uint8 damage = 0);

	/** Ce face abilitatea cand e folosita si cum se comporta de ex te face invizibil, da damage intr-o anumita zona etc. Trebuie implementata in clasele derivate */
	virtual void Behaviour();

	/** Verifica daca abilitatea poate fi folosita si invoca functia Behaviour() */
	void CastSpell();

	/* GETTERS & SETTERS */

	uint8 getCooldown() const;
	void setCooldown(uint8 cooldown);

	uint8 getCost() const;
	void setCost(uint8 cost);

	uint8 getDamage() const;
	void setDamage(uint8 damage);

	bool canBeCast() const;
	void setCanBeCast(bool value);

	FString getName() const;
	void setName(FString name);

	AMyCharacter* getCaster() const;
};

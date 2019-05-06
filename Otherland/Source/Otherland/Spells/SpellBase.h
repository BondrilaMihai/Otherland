// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellBase.generated.h"

UCLASS()
class OTHERLAND_API USpellBase : public UObject
{
	GENERATED_BODY()
	
	uint8 _cooldown;
	uint8 _cost;
	uint8 _damage;

	bool _canBeCast;

	FString _name;

public:

	USpellBase();

	~USpellBase();

	void init(uint8 cooldown, uint8 cost, FString name, bool canBeCast, uint8 damage = 0);

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
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellBase.h"
#include "TimerManager.h"

USpellBase::USpellBase()
	: _cooldown(0), _cost(0), _damage(0), _canBeCast(true), _name("UNDEFINED")
{
}

USpellBase::~USpellBase()
{
}

void USpellBase::init(uint8 cooldown, uint8 currentCooldown, uint8 cost, FString name, bool canBeCast, AMyCharacter* caster, uint8 damage)
{
	_cooldown = cooldown;
	_currentCooldown = currentCooldown;
	_cost = cost;
	_name = name;
	_canBeCast = canBeCast;
	_damage = damage;
	_caster = caster;
}

void USpellBase::Behaviour()
{
}

void USpellBase::PlaySound()
{
}

void USpellBase::CastSpell()
{
	if (getCaster()->getEnergy() && !(getCaster()->getEnergy() - getCost() < getCaster()->getMinEnergy()))
	{
		getCaster()->setEnergy(getCaster()->getEnergy() - getCost());
		StartCooldown();
		Behaviour();
		PlaySound();
	}
}

void USpellBase::StartCooldown()
{
	setCurrentCooldown(getCooldown());

	FTimerHandle UnusedHandle;

	getCaster()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &USpellBase::RefreshCooldown, getCooldown(), false);
}

void USpellBase::RefreshCooldown()
{
	setCurrentCooldown(0);
}

uint8 USpellBase::getCooldown() const
{
	return _cooldown;
}

void USpellBase::setCooldown(uint8 cooldown)
{
	_cooldown = cooldown;
}

uint8 USpellBase::getCurrentCooldown() const
{
	return _currentCooldown;
}

void USpellBase::setCurrentCooldown(uint8 cooldown)
{
	_currentCooldown = cooldown;
}

uint8 USpellBase::getCost() const
{
	return _cost;
}

void USpellBase::setCost(uint8 cost)
{
	_cost = cost;
}

uint8 USpellBase::getDamage() const
{
	return _damage;
}

void USpellBase::setDamage(uint8 damage)
{
	_damage = damage;
}

bool USpellBase::canBeCast() const
{
	return _canBeCast;
}

void USpellBase::setCanBeCast(bool value)
{
	_canBeCast = value;
}

FString USpellBase::getName() const
{
	return _name;
}

void USpellBase::setName(FString name)
{
	_name = name;
}

AMyCharacter* USpellBase::getCaster() const
{
	return _caster;
}

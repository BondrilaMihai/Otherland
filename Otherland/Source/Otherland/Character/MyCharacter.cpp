// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Controller.h"

/* AMyCharacter */

AMyCharacter::AMyCharacter()
	: _isDead(false), _health(0), _energy(0), _damage(0), _maxHealth(0), _minHealth(0), _maxEnergy(0), _minEnergy(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AMyCharacter::AMyCharacter(bool isDead, int32 health, int32 energy, uint8 damage, int32 maxHealth, int32 minHealth, int32 maxEnergy, int32 minEnergy)
	: _isDead(isDead), _health(health), _energy(energy), _damage(damage), _maxHealth(maxHealth), _minHealth(minHealth), _maxEnergy(maxEnergy), _minEnergy(minEnergy)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

ECharacterStates AMyCharacter::getCharacterState() const
{
	return _characterState;
}

void AMyCharacter::setCharacterState(ECharacterStates state)
{
	_characterState = state;
}

int32 AMyCharacter::getHealth() const
{
	return _health;
}

void AMyCharacter::setHealth(int32 amount)
{
	if (amount < _minHealth)
		_health = 0;

	//else if(_health + amount > _maxHealth)
		//_health = _maxHealth;

	else
		_health = amount;
}

uint8 AMyCharacter::getDamage() const
{
	return _damage;
}

void AMyCharacter::setDamage(uint8 amount)
{
	_damage = amount;
}

int32 AMyCharacter::getEnergy() const
{
	return _energy;
}

void AMyCharacter::setEnergy(int32 amount)
{
	if (_energy - amount < _minEnergy)
		_energy = 0;

	//else if(_energy + amount > _maxEnergy)
		//_energy = _maxEnergy;

	else
		_energy = amount;
}

int32 AMyCharacter::getMaxHealth() const
{
	return _maxHealth;
}

void AMyCharacter::setMaxHealth(int32 amount)
{
	_maxHealth = amount;
}

int32 AMyCharacter::getMinHealth() const
{
	return _minHealth;
}

void AMyCharacter::setMinHealth(int32 amount)
{
	_minHealth = amount;
}

int32 AMyCharacter::getMaxEnergy() const
{
	return _maxEnergy;
}

void AMyCharacter::setMaxEnergy(int32 amount)
{
	_maxEnergy = amount;
}

int32 AMyCharacter::getMinEnergy() const
{
	return _minEnergy;
}

void AMyCharacter::setMinEnergy(int32 amount)
{
	_minEnergy = amount;
}

void AMyCharacter::UpdateMaxValues(const AMyCharacter& character)
{
	_maxHealth = character.getHealth();
	_maxEnergy = character.getEnergy();
}

void AMyCharacter::MyTakeDamage(int32 amount)
{
	int32 tempAmount = amount;

	setHealth(getHealth() - tempAmount);

	if (!getHealth())
		_isDead = true;
}

bool AMyCharacter::isDead() const
{
	return _isDead;
}

void AMyCharacter::setDead(bool value)
{
	_isDead = value;
}
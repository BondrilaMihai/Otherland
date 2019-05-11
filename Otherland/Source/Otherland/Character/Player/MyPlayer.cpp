// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Controller.h"

/* AMyPlayer */

AMyPlayer::AMyPlayer()
	: AMyCharacter(false, 500, 125, 50, 500, 0, 125, 0), _isSKeyPressed(false), _energyConversion(1), _maxShield(375), _minShield(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	setCharacterState(ECharacterStates::State_Idle);
	_shield = 375;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitSpells();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindKey(EKeys::E, IE_Pressed, this, &AMyPlayer::ChooseAbility);
	InputComponent->BindKey(EKeys::S, IE_Pressed, this, &AMyPlayer::SKeyPressed);
	InputComponent->BindKey(EKeys::S, IE_Released, this, &AMyPlayer::SKeyReleased);
}

int32 AMyPlayer::getShield() const
{
	return _shield;
}

void AMyPlayer::setShield(int32 amount)
{
	if(amount < _minShield)
		_shield = 0;

	//else if(_shield + amount > _maxShield)
		//_shield =_maxShield;

	else
		_shield = amount;
}

uint8 AMyPlayer::getEnergyConversion() const
{
	return _energyConversion;
}

void AMyPlayer::setEnergyConversion(uint8 amount)
{
	if(amount > 0 && amount < 5)
		_energyConversion = amount;

	else
		_energyConversion = 1;
}

int32 AMyPlayer::getMaxShield() const
{
	return _maxShield;
}

void AMyPlayer::setMaxShield(int32 amount)
{
	_maxShield = amount;
}

int32 AMyPlayer::getMinShield() const
{
	return _minShield;
}

void AMyPlayer::setMinShield(int32 amount)
{
	_minShield = amount;
}

void AMyPlayer::UpdateMaxValues(const AMyPlayer & player)
{
	_maxHealth = player.getHealth();
	_maxShield = player.getShield();
	_maxEnergy = player.getEnergy();
}

void AMyPlayer::MyTakeDamage(int32 amount)
{
	int32 tempAmount = amount;

	if(getShield())
	{
		if(getShield() - tempAmount <= _minShield)
		{
			tempAmount -= getShield();
			setShield(_minShield);
			setHealth(getHealth() - tempAmount);
		}

		else
			setShield(getShield() - tempAmount);
	}

	else
		setHealth(getHealth() - tempAmount);

	if(!getHealth())
		_isDead = true;
}

void AMyPlayer::UpdateEnergyConversion()
{
	_energy = (_energyConversion / 4) * _maxShield;
	_shield = _maxShield - _energy;

	UpdateMaxValues(*this);
}

bool AMyPlayer::isSKeyPressed() const
{
	return _isSKeyPressed;
}

void AMyPlayer::SKeyPressed()
{
	_isSKeyPressed = true;
}

void AMyPlayer::SKeyReleased()
{
	_isSKeyPressed = false;
}

/* ABILITATI */

void AMyPlayer::InitSpells()
{
	_shadowstep = NewObject<UShadowstepSpell>();
	_shadowstep->init(0, 25, "Shadowstep", true, this, 0);

	_spiritDrop = NewObject<USpiritDropSpell>();
	_spiritDrop->init(0, 50, "SpiritDrop", true, this, 100);
}

void AMyPlayer::ChooseAbility()
{
	if ((getCharacterState() == ECharacterStates::State_Jumping) && isSKeyPressed())
		_spiritDrop->CastSpell();

	else if (getCharacterState() == ECharacterStates::State_Idle)
		_shadowstep->CastSpell();
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Controller.h"

/* AMyPlayer */

AMyPlayer::AMyPlayer()
	: _isSKeyPressed(false), _isDead(false), _health(500), _damage(50), _energyConversion(1), _maxHealth(500), _minHealth(0), _maxShield(500 - 500 / 4), _minShield(0),
	_maxEnergy(500 / 4), _minEnergy(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	setPlayerState(EPlayerStates::State_Idle);
	_energy = 500/4;
	_shield = 500 - _energy;
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

EPlayerStates AMyPlayer::getPlayerState() const
{
	return _playerState;
}

void AMyPlayer::setPlayerState(EPlayerStates state)
{
	_playerState = state;
}

int32 AMyPlayer::getHealth() const
{
	return _health;
}

void AMyPlayer::setHealth(int32 amount)
{
	if(amount < _minHealth)
		_health = 0;

	//else if(_health + amount > _maxHealth)
		//_health = _maxHealth;

	else
		_health = amount;
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

uint8 AMyPlayer::getDamage() const
{
	return _damage;
}

void AMyPlayer::setDamage(uint8 amount)
{
	_damage = amount;
}

int32 AMyPlayer::getEnergy() const
{
	return _energy;
}

void AMyPlayer::setEnergy(int32 amount)
{
	if(_energy - amount < _minEnergy)
		_energy = 0;

	//else if(_energy + amount > _maxEnergy)
		//_energy = _maxEnergy;

	else
		_energy = amount;
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

int32 AMyPlayer::getMaxHealth() const
{
	return _maxHealth;
}

void AMyPlayer::setMaxHealth(int32 amount)
{
	_maxHealth = amount;
}

int32 AMyPlayer::getMinHealth() const
{
	return _minHealth;
}

void AMyPlayer::setMinHealth(int32 amount)
{
	_minHealth = amount;
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

int32 AMyPlayer::getMaxEnergy() const
{
	return _maxEnergy;
}

void AMyPlayer::setMaxEnergy(int32 amount)
{
	_maxEnergy = amount;
}

int32 AMyPlayer::getMinEnergy() const
{
	return _minEnergy;
}

void AMyPlayer::setMinEnergy(int32 amount)
{
	_minEnergy = amount;
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

bool AMyPlayer::isDead() const
{
	return _isDead;
}

void AMyPlayer::setDead(bool value)
{
	_isDead = value;
}

/* ABILITIES */

void AMyPlayer::InitSpells()
{
	_shadowstep = NewObject<USpellBase>();
	_shadowstep->init(0, 25, "Shadowstep", true, 0);

	_spiritDrop = NewObject<USpellBase>();
	_spiritDrop->init(0, 50, "SpiritDrop", true, 100);
}

void AMyPlayer::CastSpell(const USpellBase& spell)
{
	if(getEnergy() && !(getEnergy() - spell.getCost() < _minEnergy))
	{
		setEnergy(getEnergy() - spell.getCost());

		FString name = spell.getName();

		if(name == "Shadowstep")
			StartShadowstep();

		else if(name == "SpiritDrop")
			StartSpiritDrop();
	}
}

// Choose between shadowstep and spirit slam when E is pressed
void AMyPlayer::ChooseAbility()
{
	if ((getPlayerState() == EPlayerStates::State_Jumping) && isSKeyPressed())
		CastSpell(*_spiritDrop);

	else if (getPlayerState() == EPlayerStates::State_Idle)
		CastSpell(*_shadowstep);
}

// Cast shadowstep
void AMyPlayer::StartShadowstep()
{
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	setPlayerState(EPlayerStates::State_Shadowstep);

	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyPlayer::FinishShadowstep, 4, false);
}

// Automatically called by StartShadowstep() after timer ends
void AMyPlayer::FinishShadowstep()
{
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	setPlayerState(EPlayerStates::State_Idle);
}

// Cast spirit slam
void AMyPlayer::StartSpiritDrop()
{
	LaunchCharacter(FVector(0.0f, 0.0f, -2000.0f), false, false);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Controller.h"

/* PlayerMinMaxValues */

PlayerMinMaxValues::PlayerMinMaxValues()
	: MaxHealth(0), MinHealth(0), MaxShield(0), MinShield(0), MaxEnergy(0), MinEnergy(0)
{
}

PlayerMinMaxValues::PlayerMinMaxValues(const AMyPlayer& player)
	: MinHealth(0), MinShield(0), MinEnergy(0)
{
	MaxHealth = player.getHealth();
	MaxShield = player.getShield();
	MaxEnergy = player.getEnergy();
}

void PlayerMinMaxValues::UpdateValues(const AMyPlayer& player)
{
	MaxHealth = player.getHealth();
	MaxShield = player.getShield();
	MaxEnergy = player.getEnergy();
}

/* AMyPlayer */

AMyPlayer::AMyPlayer()
	: _isSKeyPressed(false), _isDead(false), _health(500), _energyConversion(1), _damage(50)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	setPlayerState(EPlayerStates::State_Idle);
	_energy = 500/4;
	_shield = 500 - _energy;
	_playerMinMaxValues.UpdateValues(*this);
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
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

uint16 AMyPlayer::getHealth() const
{
	return _health;
}

void AMyPlayer::setHealth(uint16 amount)
{
	if(_health - amount < _playerMinMaxValues.MinHealth)
		_health = 0;

	else if(_health + amount > _playerMinMaxValues.MaxHealth)
		_health = _playerMinMaxValues.MaxHealth;

	else
		_health = amount;
}

uint16 AMyPlayer::getShield() const
{
	return _shield;
}

void AMyPlayer::setShield(uint16 amount)
{
	if(_shield - amount < _playerMinMaxValues.MinShield)
		_shield = 0;

	else if(_shield + amount > _playerMinMaxValues.MaxShield)
		_shield = _playerMinMaxValues.MaxShield;

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

uint16 AMyPlayer::getEnergy() const
{
	return _energy;
}

void AMyPlayer::setEnergy(uint16 amount)
{
	if(_energy - amount < _playerMinMaxValues.MinEnergy)
		_energy = 0;

	else if(_energy + amount > _playerMinMaxValues.MaxEnergy)
		_energy = _playerMinMaxValues.MaxEnergy;

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

void AMyPlayer::TakeDamage(uint16 amount)
{
	uint16 tempAmount = amount;

	if(getShield())
	{
		if(getShield() - tempAmount <= _playerMinMaxValues.MinShield)
		{
			tempAmount -= getShield();
			setShield(_playerMinMaxValues.MinShield);
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
	_energy = (_energyConversion / 4) * _playerMinMaxValues.MaxShield;
	_shield = _playerMinMaxValues.MaxShield - _energy;

	_playerMinMaxValues.UpdateValues(*this);
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

// Choose between shadowstep and spirit slam when E is pressed
void AMyPlayer::ChooseAbility()
{
	if((getPlayerState() == EPlayerStates::State_Jumping) && isSKeyPressed())
		StartSpiritSlam();

	else if(getPlayerState() == EPlayerStates::State_Idle)
		StartShadowstep();
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
void AMyPlayer::StartSpiritSlam()
{
	LaunchCharacter(FVector(0.0f, 0.0f, -2000.0f), false, false);
}
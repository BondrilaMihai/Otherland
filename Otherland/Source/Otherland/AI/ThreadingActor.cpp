// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadingActor.h"

// Sets default values
AThreadingActor::AThreadingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AThreadingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThreadingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AssassinBossDecisionThread::AssassinBossDecisionThread(AAssassinBoss& user)
	: _canDecide(true)
{
	_thread = FRunnableThread::Create(this, TEXT("AssassinBossDecisionThread"), 0, TPri_BelowNormal);
	_user = &user;
}

AssassinBossDecisionThread::~AssassinBossDecisionThread()
{
	_thread->Kill();
	delete _thread;
	_thread = NULL;
	_user = NULL;
}

uint32 AssassinBossDecisionThread::Run()
{
	//while(_canDecide)
		//Decide();

	return 0;
}

void AssassinBossDecisionThread::Stop()
{
	_canDecide = false;
}

bool AssassinBossDecisionThread::CanDecide()
{
	return _canDecide;
}

void AssassinBossDecisionThread::Decide()
{
	// TO DO DAGGER RAIN

	//uint8 distance = _user->checkPlayerDistance();

	int32 distance = FMath::RandRange(0, 2);

	switch (distance)
	{
		/** Distanta mica */
	case 0:
	{
		/** Cooldown-ul nu este 0 */
		if (_user->_shadowstep->getCurrentCooldown())
		{
			_user->MeleeAttack();
			FPlatformProcess::Sleep(1);

			if (!(_user->_flicker->getCurrentCooldown()))
				_user->_flicker->CastSpell();
		}
		/** Cooldown-ul este 0 */
		else
		{
			_user->_shadowstep->CastSpell();
			FPlatformProcess::Sleep(4);

			int32 r = FMath::RandRange(1, 100);

			if (r < 51 && !(_user->_flicker->getCurrentCooldown()))
				_user->_flicker->CastSpell();

			if (r >= 51 && !(_user->_daggFlash->getCurrentCooldown()))
				_user->_daggFlash->CastSpell();
		}

		break;
	}

	/** Distanta medie*/
	case 1:
	{
		if (!(_user->_flicker->getCurrentCooldown()) && !(_user->_daggFlash->getCurrentCooldown()))
		{
			_user->_flicker->CastSpell();
			FPlatformProcess::Sleep(1.5f);
			_user->_daggFlash->CastSpell();
		}

		else
			_user->JumpBack(_user->IsMovingRight());

		break;
	}

	/** Distanta mare */
	case 2:
	{
		while (_user->_daggTp->getCurrentCooldown())
		{
			_user->WalkBack(_user->IsMovingRight());
		}

		_user->_daggTp->CastSpell();

		if (!(_user->_flicker->getCurrentCooldown()))
			_user->_flicker->CastSpell();

		else
		{
			FPlatformProcess::Sleep(0.5f);

			int32 r = FMath::RandRange(1, 100);

			// TO DO
		}

		break;
	}
	}

	FPlatformProcess::Sleep(2);
}

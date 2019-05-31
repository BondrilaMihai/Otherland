// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "Runnable.h"
#include "Otherland/Enemies/AssassinBoss.h"
#include "ThreadingActor.generated.h"

UCLASS()
class OTHERLAND_API AThreadingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThreadingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

class AssassinBossDecisionThread : public FRunnable
{
	class AAssassinBoss* _user;

	/** Thread-ul pe care ruleaza interfata FRunnable */
	FRunnableThread* _thread;

	/** Daca AI-ul poate incepe sa ia o decizie */
	bool _canDecide;

public:

	AssassinBossDecisionThread(class AAssassinBoss& user);
	virtual ~AssassinBossDecisionThread();

	/* FUNCTII DIN INTERFATA FRunnable */

	virtual uint32 Run();
	virtual void Stop();

	bool CanDecide();

	/** Functia care se ocupa de logica si de ce alegere va lua AI-ul */
	void Decide();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class AMyPlayer;

// Different states of the player
UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	State_Idle			UMETA(DisplayName = "Idle"),
	State_Walking		UMETA(DisplayName = "Walking"),
	State_Dead			UMETA(DisplayName = "Dead"),
	State_Jumping		UMETA(DisplayName = "Jumping"),
	State_Hit			UMETA(DisplayName = "Hit"),
	State_Shadowstep	UMETA(DisplayName = "Shadowstep")
};

struct PlayerMinMaxValues
{
	uint16 MaxHealth;
	uint16 MinHealth;
	uint16 MaxShield;
	uint16 MinShield;
	uint16 MaxEnergy;
	uint16 MinEnergy;

	PlayerMinMaxValues();
	PlayerMinMaxValues(const AMyPlayer& player);
	void UpdateValues(const AMyPlayer& player);
};

UCLASS()
class OTHERLAND_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool _isSKeyPressed;
	bool _isDead;

	PlayerMinMaxValues _playerMinMaxValues;

	UPROPERTY(BlueprintGetter = getPlayerState, BlueprintSetter = setPlayerState, Category = "Test")
	EPlayerStates _playerState;

	uint16 _health;
	uint16 _shield;
	uint8 _damage;
	uint16 _energy; 
	uint8 _energyConversion; // Can have values 1, 2, 3 or 4 representing 1/4, 2/4, 3/4 and 4/4 of the shield that can be used for spell casts

public:

	UFUNCTION(BlueprintGetter, Category = "Test")
	EPlayerStates getPlayerState() const;

	UFUNCTION(BlueprintSetter, Category = "Test")
	void setPlayerState(EPlayerStates state);

	uint16 getHealth() const;
	void setHealth(uint16 amount);

	uint16 getShield() const;
	void setShield(uint16 amount);

	uint8 getDamage() const;
	void setDamage(uint8 amount);

	uint16 getEnergy() const;
	void setEnergy(uint16 amount);

	uint8 getEnergyConversion() const;
	void setEnergyConversion(uint8 amount);

	UFUNCTION()
	void TakeDamage(uint16 amount);

	UFUNCTION()
	void UpdateEnergyConversion();

	bool isSKeyPressed() const;
	void SKeyPressed();
	void SKeyReleased();

	bool isDead() const;
	void setDead(bool value);

	/* ABILITIES */

	// Chooses between shadowstep or spirit slam when E is pressed
	void ChooseAbility();

	// Cast shadowstep
	void StartShadowstep();
	void FinishShadowstep();

	// Cast spirit slam
	void StartSpiritSlam();
};

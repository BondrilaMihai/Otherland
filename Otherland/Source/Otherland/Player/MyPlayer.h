// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "Spells/SpellBase.h"
#include "MyPlayer.generated.h"

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

	UPROPERTY(BlueprintGetter = getPlayerState, BlueprintSetter = setPlayerState, Category = "Test")
	EPlayerStates _playerState;

	/* CURRENT PLAYER VALUES */
	
	UPROPERTY(BlueprintGetter = getHealth, Category = "Test")
	int32 _health;
	UPROPERTY(BlueprintGetter = getShield, Category = "Test")
	int32 _shield;
	UPROPERTY(BlueprintGetter = getEnergy, Category = "Test")
	int32 _energy;
	UPROPERTY(BlueprintGetter = getDamage, Category = "Test")
	uint8 _damage;
	UPROPERTY(BlueprintGetter = getEnergyConversion, Category = "Test")
	uint8 _energyConversion; // Can have values 1, 2, 3 or 4 representing 1/4, 2/4, 3/4 and 4/4 of the shield that can be used for spell casts

	/* MIN & MAX PLAYER VALUES */
	UPROPERTY(BlueprintGetter = getMaxHealth, Category = "Test")
	int32 _maxHealth;
	UPROPERTY(BlueprintGetter = getMinHealth, Category = "Test")
	int32 _minHealth;
	UPROPERTY(BlueprintGetter = getMaxShield, Category = "Test")
	int32 _maxShield;
	UPROPERTY(BlueprintGetter = getMinShield, Category = "Test")
	int32 _minShield;
	UPROPERTY(BlueprintGetter = getMaxEnergy, Category = "Test")
	int32 _maxEnergy;
	UPROPERTY(BlueprintGetter = getMinEnergy, Category = "Test")
	int32 _minEnergy;

	/* ABILITIES */

	UPROPERTY()
	USpellBase* _shadowstep;
	UPROPERTY()
	USpellBase* _spiritDrop;

public:

	UFUNCTION(BlueprintGetter, Category = "Test")
	EPlayerStates getPlayerState() const;

	UFUNCTION(BlueprintSetter, Category = "Test")
	void setPlayerState(EPlayerStates state);

	/* CURRENT PLAYER VALUES GETTERS & SETTERS */

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getHealth() const;
	void setHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getShield() const;
	void setShield(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getEnergy() const;
	void setEnergy(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	uint8 getDamage() const;
	void setDamage(uint8 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	uint8 getEnergyConversion() const;
	void setEnergyConversion(uint8 amount);

	/* MIN & MAX PLAYER VALUES GETTERS & SETTERS */

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMaxHealth() const;
	void setMaxHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMinHealth() const;
	void setMinHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMaxShield() const;
	void setMaxShield(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMinShield() const;
	void setMinShield(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMaxEnergy() const;
	void setMaxEnergy(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
	int32 getMinEnergy() const;
	void setMinEnergy(int32 amount);

	void UpdateMaxValues(const AMyPlayer& player);

	/* MISC */

	UFUNCTION(BlueprintCallable, Category = "Test")
	void MyTakeDamage(int32 amount);

	UFUNCTION(BlueprintCallable, Category = "Test")
	void UpdateEnergyConversion();

	bool isSKeyPressed() const;
	void SKeyPressed();
	void SKeyReleased();

	bool isDead() const;
	void setDead(bool value);

	/* ABILITIES */

	void InitSpells();
	void CastSpell(const USpellBase& spell);

	// Chooses between shadowstep or spirit slam when E is pressed
	void ChooseAbility();

	// Cast shadowstep
	void StartShadowstep();
	void FinishShadowstep();

	// Cast spirit slam
	void StartSpiritDrop();
};

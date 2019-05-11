// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/MyCharacter.h"
#include "Spells/ShadowstepSpell.h"
#include "Spells/SpiritDropSpell.h"
#include "MyPlayer.generated.h"

UCLASS()
class OTHERLAND_API AMyPlayer : public AMyCharacter
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

	/* VALORILE CURENTE - SCUT, CONVERTIRE ENERGIE */
	
	UPROPERTY(BlueprintGetter = getShield, Category = "Test")
		int32 _shield;
	UPROPERTY(BlueprintGetter = getEnergyConversion, Category = "Test")
		uint8 _energyConversion; // Can have values 1, 2, 3 or 4 representing 1/4, 2/4, 3/4 and 4/4 of the shield that can be used for spell casts

	/* VALORILE MAXIME & MINIME - SCUT */
	UPROPERTY(BlueprintGetter = getMaxShield, Category = "Test")
		int32 _maxShield;
	UPROPERTY(BlueprintGetter = getMinShield, Category = "Test")
		int32 _minShield;

	/* ABILITATI */

	UPROPERTY()
		UShadowstepSpell* _shadowstep;
	UPROPERTY()
		USpiritDropSpell* _spiritDrop;

public:

	/* GETTERS & SETTERS PENTRU VALORILE CURENTE */

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getShield() const;
	void setShield(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		uint8 getEnergyConversion() const;
	void setEnergyConversion(uint8 amount);

	/* GETTERS & SETTERS PENTRU VALORILE MAXIME & MINIME */

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMaxShield() const;
	void setMaxShield(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMinShield() const;
	void setMinShield(int32 amount);

	void UpdateMaxValues(const AMyPlayer& player);

	/* MISC */

	void MyTakeDamage(int32 amount);

	UFUNCTION(BlueprintCallable, Category = "Test")
	void UpdateEnergyConversion();

	bool isSKeyPressed() const;
	void SKeyPressed();
	void SKeyReleased();

	/* ABILITATI */

	/** Initiaza abilitatile */
	void InitSpells();

	/** Alege ce abilitate sa foloseasca in anumite cazuri */
	void ChooseAbility();
};

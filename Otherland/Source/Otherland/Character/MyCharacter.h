#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

/** Diferitele stari ale caracterului */
UENUM(BlueprintType)
enum class ECharacterStates : uint8
{
	State_Idle			UMETA(DisplayName = "Idle"),
	State_Walking		UMETA(DisplayName = "Walking"),
	State_Dead			UMETA(DisplayName = "Dead"),
	State_Jumping		UMETA(DisplayName = "Jumping"),
	State_Hit			UMETA(DisplayName = "Hit"),
	State_DealingDamage UMETA(DisplayName = "DealingDamage"),
	State_Shadowstep	UMETA(DisplayName = "Shadowstep"),
	State_SpiritDrop	UMETA(DisplayName = "SpiritDrop"),
	State_DaggerTp		UMETA(DisplayName = "DaggerTeleport"),
	State_DaggerFlash	UMETA(DisplayName = "DaggerFlash"),
	State_DaggerRain	UMETA(DisplayName = "DaggerRain"),
	State_Flicker		UMETA(DisplayName = "Flicker")
};

/* Clasa de baza pentru caractere, cand faceti un caracter nou il derivati din asta, de ex un inamic */

UCLASS()
class OTHERLAND_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	AMyCharacter(bool isDead, int32 health, int32 energy, uint8 damage, int32 maxHealth, int32 minHealth, int32 maxEnergy, int32 minEnergy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(BlueprintGetter = isDead, Category = "Test")
		bool _isDead;

	bool _threshhold25;
	bool _threshhold50;
	bool _threshhold75;

	/** Starea caracterului */
	UPROPERTY(BlueprintGetter = getCharacterState, BlueprintSetter = setCharacterState, Category = "Test")
		ECharacterStates _characterState;

	/* VALORILE CURENTE - VIATA, ENERGIE, DAMAGE */

	UPROPERTY(BlueprintGetter = getHealth, Category = "Test")
		int32 _health;
	UPROPERTY(BlueprintGetter = getEnergy, Category = "Test")
		int32 _energy;
	UPROPERTY(BlueprintGetter = getDamage, Category = "Test")
		uint8 _damage;

	/* VALORILE MAXIME & MINIME - VIATA, ENERGIE */

	UPROPERTY(BlueprintGetter = getMaxHealth, Category = "Test")
		int32 _maxHealth;
	UPROPERTY(BlueprintGetter = getMinHealth, Category = "Test")
		int32 _minHealth;
	UPROPERTY(BlueprintGetter = getMaxEnergy, Category = "Test")
		int32 _maxEnergy;
	UPROPERTY(BlueprintGetter = getMinEnergy, Category = "Test")
		int32 _minEnergy;

	/* COMPONENTELE */

	/** Componenta care va reda un sunet specific unei abilitati cand este folosita. */
	UPROPERTY()
		UAudioComponent* _spellSound;

public:

	UAudioComponent* getSpellSoundComponent() const;
	void setSpellSoundComponentSound(USoundCue sound);

	/* GETTER & SETTER PENTRU STARILE CARACTERULUI */

	UFUNCTION(BlueprintGetter, Category = "Test")
		ECharacterStates getCharacterState() const;

	UFUNCTION(BlueprintSetter, Category = "Test")
		void setCharacterState(ECharacterStates state);

	/* GETTERS & SETTERS PENTRU VALORILE CURENTE */

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getHealth() const;
	void setHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getEnergy() const;
	void setEnergy(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		uint8 getDamage() const;
	void setDamage(uint8 amount);

	/* GETTERS & SETTERS PENTRU VALORILE MAXIME & MINIME */

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMaxHealth() const;
	void setMaxHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMinHealth() const;
	void setMinHealth(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMaxEnergy() const;
	void setMaxEnergy(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		int32 getMinEnergy() const;
	void setMinEnergy(int32 amount);

	/** Modifica valorile maxime - suprascrieti in clasele derivate daca adaugati valori noi inafara de viata si energie */
	void UpdateMaxValues(const AMyCharacter& character);

	/* MISC */

	/** Functia de luat damage - suprascrieti in clasele derivate daca adaugati alte proprietati inafara de viata cum ar fi un scut etc. */
	UFUNCTION(BlueprintCallable, Category = "Test")
		virtual void MyTakeDamage(int32 amount);

	UFUNCTION(BlueprintGetter, Category = "Test")
		bool isDead() const;

	void setDead(bool value);
};


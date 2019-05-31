// Fill out your copyright notice in the Description page of Project Settings.

#include "AssassinBoss.h"
#include "AI/ThreadingActor.h"

// Sets default values
AAssassinBoss::AAssassinBoss()
	: AMyCharacter(false, 1000, 1, 50, 1000, 0, 1, 0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	setCharacterState(ECharacterStates::State_Idle);

	_sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	_sprite->SetupAttachment(RootComponent);
	_sprite->SetRelativeLocation(FVector(0.0f, 0.0f, 21.0f));
	_sprite->SetFlipbook(Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Game/Sprites/AssassinsSprites/Boss/DaggerTp/A_Idle.A_Idle'"))));
	_sprite->SetGenerateOverlapEvents(false);
	_sprite->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	_sprite->CanCharacterStepUpOn = ECB_No;
	_sprite->SetNotifyRigidBodyCollision(false);

	_daggTpArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DaggerTpArrow"));
	_daggTpArrow->SetupAttachment(RootComponent);
	_daggTpArrow->SetRelativeLocation(FVector(-40.0f, 0.0f, 11.0f));
	_daggTpArrow->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	_decisionThread = new AssassinBossDecisionThread(*this);
}

AAssassinBoss::~AAssassinBoss()
{
	_decisionThread->Stop();
	delete _decisionThread;
	_decisionThread = NULL;
}

// Called when the game starts or when spawned
void AAssassinBoss::BeginPlay()
{
	Super::BeginPlay();
	_decisionThread->Run();
}

// Called every frame
void AAssassinBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAssassinBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

uint8 AAssassinBoss::checkPlayerDistance()
{
	/** Distanta mare default */
	uint8 result = 2;

	float distance = GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	/** Distanta mica */
	if (distance <= SHORT_DISTANCE && distance >= (-1.0f * SHORT_DISTANCE))
		result = 0;

	/** Distanta medie */
	else if (distance <= MEDIUM_DISTANCE && distance >= (-1.0f * MEDIUM_DISTANCE))
		result = 1;

	return result;
}

void AAssassinBoss::JumpBack(bool isFacingRight)
{
	if (isFacingRight)
		LaunchCharacter(FVector(-700.0f, 0.0f, 300.0f), false, false);

	else
		LaunchCharacter(FVector(700.0f, 0.0f, 300.0f), false, false);
}

void AAssassinBoss::WalkBack(bool isFacingRight)
{
	if (isFacingRight)
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), -1.0f);

	else
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f));
}

void AAssassinBoss::MeleeAttack()
{
}

void AAssassinBoss::RangedAttack()
{
}

bool AAssassinBoss::SpellReady(const USpellBase& spell)
{
	return (spell.getCooldown() == 0);
}

bool AAssassinBoss::IsMovingRight()
{
	return GetControlRotation().Yaw == 180.0f;
}

UPaperFlipbookComponent* AAssassinBoss::getSprite() const
{
	return _sprite;
}

void AAssassinBoss::setSprite(UPaperFlipbook* sprite)
{
	_sprite->SetFlipbook(sprite);
}

void AAssassinBoss::InitSpells()
{
	_shadowstep = NewObject<UShadowstepSpell>();
	_shadowstep->init(9, 0, 0, "Shadowstep", true, this, 0);

	_daggFlash = NewObject<UDaggerFlashSpell>();
	_daggFlash->init(5, 0, 0, "DaggerFlash", true, this, 150);

	_daggRain = NewObject<UDaggerRainSpell>();
	_daggRain->init(0, 0, 0, "DaggerRain", true, this, 50);

	_daggTp = NewObject<UDaggerTeleportSpell>();
	_daggTp->init(5, 0, 0, "DaggerTeleport", true, this, 100);

	_flicker = NewObject<UFlickerSpell>();
	_flicker->init(5, 0, 0, "Flicker", true, this, 0);
}


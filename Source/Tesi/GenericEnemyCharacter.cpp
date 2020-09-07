// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericEnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Classes/AIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGenericEnemyCharacter::AGenericEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**/
	/*Create Component
	/**/
	//Damage Collider (Collider that damage Main Character)
	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollider"));
	//DamageCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("EnemySocket"));

	/**/
	/*Enemy Stats
	/**/
	//Max Health
	MaxHealth = 100.f;
	//Current (At every frame) Health
	Health = 75.f;
	//Bool that check if he is alive
	bEnemyIsAlive = true;

	/**/
	/*Combat Variables
	/**/
	//Damage Output
	Damage = 10.f;
	//bool that check if enemy is attacking
	bIsAttacking = false;
	//Set Attack Delay (Max)
	AttackMaxTime = 3.f;
	//Set Attack Delay (Min)
	AttackMinTime = 0.5f;

	/**/
	/*Combat Paticle Variables
	/**/
	DamagedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DamagedParticle"));
	DamagedParticle->SetupAttachment(GetMesh());

	/**/
	/*Death Variables
	/**/
	//Timer in order to destroy The enemy Instance
	DestroyObjectDelay = 3.f;

}

// Called when the game starts or when spawned
void AGenericEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//
	EnemyPosition = GetActorLocation();

}

// Called every frame
void AGenericEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemyPosition = GetActorLocation();

}

// Called to bind functionality to input
void AGenericEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGenericEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		Health -= DamageAmount;
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}
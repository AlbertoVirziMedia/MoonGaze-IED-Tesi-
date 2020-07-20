// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Classes/AIController.h"
#include "BossAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"
#include "BossAnimInstance.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABossCharacter::ABossCharacter()
{
	/**/
	/*Create Component
	/**/
	//Damage Collider (Collider that damage Main Character)
	DamageColliderDx = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageColliderDX"));
	DamageColliderDx->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("BossDxSocket"));

	DamageColliderLanterna = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageColliderLanterna"));
	DamageColliderLanterna->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("BossLanternaSocket"));

}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<ABossAIController>(GetController());
	if (!AIController)
	{

	}
	else
	{

	}

	/**/
	/*Bind Action On Overlap of DamageCollider Component
	/**/
	if (!DamageCollider)
	{

	}
	else
	{
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &ABossCharacter::DamageColliderBeginOverlap);
		DamageCollider->OnComponentEndOverlap.AddDynamic(this, &ABossCharacter::DamageColliderEndOverlap);
	}


	/**/
	/*AnimInstance Setting
	/**/
	BossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (!BossAnimInstance)
	{

	}
	else
	{

	}

}

void ABossCharacter::DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ABossCharacter::DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

float ABossCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	bIsGettingDameged = true;
	if (Health - DamageAmount <= 0.f)
	{
		BossAnimInstance->DeathAnim();
		bEnemyIsAlive = false;
		AIController->StopTree();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABossCharacter::Die()
{

}

void ABossCharacter::DeadEnd()
{

}

void ABossCharacter::Disappear()
{

}

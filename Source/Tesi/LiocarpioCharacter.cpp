// Fill out your copyright notice in the Description page of Project Settings.

#include "LiocarpioCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Classes/AIController.h"
#include "LiocarpioAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"
#include "LiocarpioAnimInstance.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ALiocarpioCharacter::ALiocarpioCharacter()
{

	/**/
	/*Create Component
	/**/
	//Damage Collider (Collider that damage Main Character)
	DamageColliderDx = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageColliderDx"));
//	DamageColliderDx->SetupAttachment(GetMesh(), FName("GranchioDxSocket"));

	bCanTakeDamage = true;
	TakeDamageStop = 3.f;
}

void ALiocarpioCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<ALiocarpioAIController>(GetController());
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
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &ALiocarpioCharacter::DamageColliderBeginOverlap);
		DamageCollider->OnComponentEndOverlap.AddDynamic(this, &ALiocarpioCharacter::DamageColliderEndOverlap);
	}

	/**/
	/*Bind Action On Overlap of DamageCollider Component
	/**/
	if (!DamageColliderDx)
	{

	}
	else
	{
		DamageColliderDx->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GranchioDxSocket"));
		DamageColliderDx->OnComponentBeginOverlap.AddDynamic(this, &ALiocarpioCharacter::DamageColliderDxBeginOverlap);
		DamageColliderDx->OnComponentEndOverlap.AddDynamic(this, &ALiocarpioCharacter::DamageColliderDxEndOverlap);
	}

	/**/
	/*AnimInstance Setting
	/**/
	LAnimInstance = Cast<ULiocarpioAnimInstance>(GetMesh()->GetAnimInstance());
	if (!LAnimInstance)
	{

	}
	else
	{

	}

}

void ALiocarpioCharacter::DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ALiocarpioCharacter::DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ALiocarpioCharacter::DamageColliderDxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ALiocarpioCharacter::DamageColliderDxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ALiocarpioCharacter::MeleeAttack()
{

}

void ALiocarpioCharacter::MeleeAttackEnd()
{

}

float ALiocarpioCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{

	if (LAnimInstance)
	{
		if (bCanTakeDamage)
		{
			LAnimInstance->TakeDamageAnim();
			bCanTakeDamage = false;
			GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &ALiocarpioCharacter::ResetTakeDamage, TakeDamageStop, false);
		}
	}
	bIsGettingDameged = true;
	if (Health - DamageAmount <= 0.f)
	{
		ALiocarpioCharacter::Die();
		bEnemyIsAlive = false;
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ALiocarpioCharacter::ResetTakeDamage()
{
	bCanTakeDamage = true;
}

void ALiocarpioCharacter::Die()
{
	if (AIController)
	{
		AIController->LBehaviorTreeComp->StopTree();
	}
	if (LAnimInstance)
	{
		LAnimInstance->DeathAnim();
	}
}

void ALiocarpioCharacter::DeadEnd()
{

}

void ALiocarpioCharacter::Disappear()
{

}


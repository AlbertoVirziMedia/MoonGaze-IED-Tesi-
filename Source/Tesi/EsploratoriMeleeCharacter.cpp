// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Classes/AIController.h"
#include "EsploratoriMeleeAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"
#include "EsploratoriMeleeAnimInstance.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AEsploratoriMeleeCharacter::AEsploratoriMeleeCharacter()
{
	bCanTakeDamage = true;
	TakeDamageStop = 3.f;

	//
	bPlayDeathOnce = true;
}

void AEsploratoriMeleeCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<AEsploratoriMeleeAIController>(GetController());
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
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::DamageColliderBeginOverlap);
		DamageCollider->OnComponentEndOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::DamageColliderEndOverlap);
	}

	/**/
	/*AnimInstance Setting
	/**/
	EMAnimInstance = Cast<UEsploratoriMeleeAnimInstance>(GetMesh()->GetAnimInstance());
	if (!EMAnimInstance)
	{

	}
	else
	{

	}

}

void AEsploratoriMeleeCharacter::DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void AEsploratoriMeleeCharacter::DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

float AEsploratoriMeleeCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (bPlayDeathOnce)
	{
		if (EMAnimInstance)
		{
			if (bCanTakeDamage)
			{
				EMAnimInstance->TakeDamageAnim();
				bCanTakeDamage = false;
				GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AEsploratoriMeleeCharacter::ResetTakeDamage, TakeDamageStop, false);
			}
		}
		bIsGettingDameged = true;
		if (Health - DamageAmount <= 0.f)
		{
			EMAnimInstance->DeathAnim();
			bEnemyIsAlive = false;
			AIController->StopTree();
			bPlayDeathOnce = false;
		}
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEsploratoriMeleeCharacter::ResetTakeDamage()
{
	bCanTakeDamage = true;
}

void AEsploratoriMeleeCharacter::Die()
{

}

void AEsploratoriMeleeCharacter::DeadEnd()
{

}

void AEsploratoriMeleeCharacter::Disappear()
{

}

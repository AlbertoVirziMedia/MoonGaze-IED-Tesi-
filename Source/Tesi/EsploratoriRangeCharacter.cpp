// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriRangeCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Classes/AIController.h"
#include "EsploratoriRangeAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"
#include "EsploratoriRangeAnimInstance.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AEsploratoriRangeCharacter::AEsploratoriRangeCharacter()
{
	/**/
	/*Create Component
	/**/
	//Damage Collider (Collider that damage Main Character)
	DamageColliderBastone = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageColliderBastone"));
	DamageColliderBastone->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("DamageColliderBastone"));

	bCanTakeDamage = true;
	TakeDamageStop = 3.f;

	//
	bPlayDeathOnce = true;
}

void AEsploratoriRangeCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<AEsploratoriRangeAIController>(GetController());
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
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEsploratoriRangeCharacter::DamageColliderBeginOverlap);
		DamageCollider->OnComponentEndOverlap.AddDynamic(this, &AEsploratoriRangeCharacter::DamageColliderEndOverlap);
	}

	/**/
	/*AnimInstance Setting
	/**/
	ERAnimInstance = Cast<UEsploratoriRangeAnimInstance>(GetMesh()->GetAnimInstance());
	if (!ERAnimInstance)
	{

	}
	else
	{

	}

}

void AEsploratoriRangeCharacter::DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void AEsploratoriRangeCharacter::DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

float AEsploratoriRangeCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (bPlayDeathOnce)
	{
		if (ERAnimInstance)
		{
			if (bCanTakeDamage)
			{
				ERAnimInstance->TakeDamageAnim();
				bCanTakeDamage = false;
				GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AEsploratoriRangeCharacter::ResetTakeDamage, TakeDamageStop, false);
			}
		}
		bIsGettingDameged = true;
		if (Health - DamageAmount <= 0.f)
		{
			ERAnimInstance->DeathAnim();
			bEnemyIsAlive = false;
			AIController->StopTree();
		}
	}	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEsploratoriRangeCharacter::ResetTakeDamage()
{
	bCanTakeDamage = true;
}

void AEsploratoriRangeCharacter::Die()
{

}

void AEsploratoriRangeCharacter::DeadEnd()
{

}

void AEsploratoriRangeCharacter::Disappear()
{

}


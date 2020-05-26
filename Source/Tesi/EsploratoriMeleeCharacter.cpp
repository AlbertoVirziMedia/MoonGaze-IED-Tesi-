// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Classes/AIController.h"
#include "EsploratoriMeleeAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"

AEsploratoriMeleeCharacter::AEsploratoriMeleeCharacter()
{
	
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
		GLog->Log("Ai Controller non creato");
	}
	else
	{
		GLog->Log("AI");
	}

	//Register the function that is going to fire when the character sees a Pawn
	if (PawnSensingComp)
	{
		//Sight Sense
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEsploratoriMeleeCharacter::OnSeePlayer);
		//Hearing Sense
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AEsploratoriMeleeCharacter::OnHearNoise);
	}

	/**/
	/*Bind Action On Overlap of ZoneOfCombat Component
	/**/
	if (!ZoneOfCombat)
	{
		GLog->Log("Zone of Combat Non Creato");
	}
	else
	{
		GLog->Log("Zone of Combat Creato");
		//ZoneOfCombat Binding
		ZoneOfCombat->OnComponentBeginOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::OnZoneOfCombatBeginOverlap);
		ZoneOfCombat->OnComponentEndOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::OnZoneOfCombatEndOverlap);
	}
	/**/
	/*Bind Action On Overlap of DamageCollider Component
	/**/
	if (!DamageCollider)
	{
		GLog->Log("DamageCollider Non Creato");
	}
	else
	{
		GLog->Log("DamageCollider Creato");
		DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::DamageColliderBeginOverlap);
		DamageCollider->OnComponentEndOverlap.AddDynamic(this, &AEsploratoriMeleeCharacter::DamageColliderEndOverlap);
	}

}

void AEsploratoriMeleeCharacter::OnSeePlayer(APawn* Pawn)
{
	//Set the seen target on the blackboard
	if (AIController)
	{
		GLog->Log("I See you");
		AIController->SetSeenTarget(Pawn);
		if (Pawn)
		{
			class AMainCharacter* MainCharacter = Cast<AMainCharacter>(Pawn);
			if (MainCharacter)
			{
				MainCharacter->CombatTarget = this;
			}
		}
	}

}

void AEsploratoriMeleeCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	//We don't want to hear ourselves
	if (AIController && PawnInstigator != this)
	{
		GLog->Log("I hear you");
		//Updates our target based on what we've heard.
		AIController->SetSensedTarget(PawnInstigator);
	}

}

void AEsploratoriMeleeCharacter::OnZoneOfCombatBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AIController)
	{
		AIController->ChangeBoolIsInZoneOfCombat();
	}
	
}

void AEsploratoriMeleeCharacter::OnZoneOfCombatEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AEsploratoriMeleeCharacter::DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void AEsploratoriMeleeCharacter::DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AEsploratoriMeleeCharacter::MeleeAttack()
{

}

void AEsploratoriMeleeCharacter::MeleeAttackEnd()
{

}

float AEsploratoriMeleeCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	return DamageAmount;
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

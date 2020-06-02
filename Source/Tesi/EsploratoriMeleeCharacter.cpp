// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"
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

void AEsploratoriMeleeCharacter::OnZoneOfCombatBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
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

void AEsploratoriMeleeCharacter::Die()
{

}

void AEsploratoriMeleeCharacter::DeadEnd()
{

}

void AEsploratoriMeleeCharacter::Disappear()
{

}

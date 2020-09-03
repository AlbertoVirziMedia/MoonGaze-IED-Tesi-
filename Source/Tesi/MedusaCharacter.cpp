// Fill out your copyright notice in the Description page of Project Settings.


#include "MedusaCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MeduseAIController.h"
#include "MeduseAnimInstance.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"

AMedusaCharacter::AMedusaCharacter()
{
	bCanTakeDamage = true;
	TakeDamageStop = 3.f;

	//
	bPlayDeathOnce = true;
}

void AMedusaCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<AMeduseAIController>(GetController());
	if (!AIController)
	{

	}
	else
	{

	}

	/**/
	/*AnimInstance Setting
	/**/
	MAnimInstance = Cast<UMeduseAnimInstance>(GetMesh()->GetAnimInstance());
	if (!MAnimInstance)
	{
		GLog->Log("Medusa not Anim");
	}
	else
	{
		GLog->Log("Medusa Anim");
	}
}

float AMedusaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (bPlayDeathOnce)
	{
		bIsGettingDameged = true;
		if (MAnimInstance)
		{
			if (bCanTakeDamage)
			{
				MAnimInstance->TakeDamageAnim();
				bCanTakeDamage = false;
				GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AMedusaCharacter::ResetTakeDamage, TakeDamageStop, false);
			}
		}
		bIsGettingDameged = true;
		if (Health - DamageAmount <= 0.f)
		{
			MAnimInstance->DeathAnim();
			bEnemyIsAlive = false;
			bPlayDeathOnce = false;
		}
	}	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMedusaCharacter::ResetTakeDamage()
{
	bCanTakeDamage = true;
}

void AMedusaCharacter::Die()
{

}

void AMedusaCharacter::DeadEnd()
{

}

void AMedusaCharacter::Disappear()
{

}
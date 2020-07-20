// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriRangeAnimInstance.h"
#include "EsploratoriRangeCharacter.h"

//
void UEsploratoriRangeAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			ERCharacter = Cast<AEsploratoriRangeCharacter>(Pawn);
		}
	}
}

//
void UEsploratoriRangeAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			ERCharacter = Cast<AEsploratoriRangeCharacter>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
	}
}

void UEsploratoriRangeAnimInstance::TakeDamageAnim()
{
	if (ERCombatMontage)
	{
		Montage_Play(ERCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Reaction"), ERCombatMontage);
	}
}

void UEsploratoriRangeAnimInstance::DeathAnim()
{
	if (ERCombatMontage)
	{
		Montage_Play(ERCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Death"), ERCombatMontage);
	}
}


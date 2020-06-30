// Fill out your copyright notice in the Description page of Project Settings.


#include "LiocarpioAnimInstance.h"
#include "LiocarpioCharacter.h"

void ULiocarpioAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			LCharacter = Cast<ALiocarpioCharacter>(Pawn);
		}
	}
}

//
void ULiocarpioAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			LCharacter = Cast<ALiocarpioCharacter>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
	}
}

void ULiocarpioAnimInstance::TakeDamageAnim()
{
	if (LCombatMontage)
	{
		Montage_Play(LCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Reaction"), LCombatMontage);
	}
}

void ULiocarpioAnimInstance::DeathAnim()
{
	if (LCombatMontage)
	{
		Montage_Play(LCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Death"), LCombatMontage);
	}
}

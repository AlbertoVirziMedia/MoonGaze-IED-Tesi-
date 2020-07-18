// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "BossCharacter.h"

//
void UBossAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			BossCharacter = Cast<ABossCharacter>(Pawn);
		}
	}
}

//
void UBossAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			BossCharacter = Cast<ABossCharacter>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
	}
}

void UBossAnimInstance::DeathAnim()
{
	if (BossCombatMontage)
	{
		Montage_Play(BossCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Death"), BossCombatMontage);
	}
}

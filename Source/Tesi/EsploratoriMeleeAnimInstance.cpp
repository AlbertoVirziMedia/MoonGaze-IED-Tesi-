// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeAnimInstance.h"
#include "EsploratoriMeleeCharacter.h"

//
void UEsploratoriMeleeAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			EMCharacter = Cast<AEsploratoriMeleeCharacter>(Pawn);
		}
	}
}

//
void UEsploratoriMeleeAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			EMCharacter = Cast<AEsploratoriMeleeCharacter>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
	}
}

void UEsploratoriMeleeAnimInstance::TakeDamageAnim()
{
	if (EMCombatMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reaction"));
		Montage_Play(EMCombatMontage, 1.0f);
		Montage_JumpToSection(FName("Reaction"), EMCombatMontage);
	}
}


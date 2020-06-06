// Fill out your copyright notice in the Description page of Project Settings.


#include "MeduseAnimInstance.h"
#include "MedusaCharacter.h"

void UMeduseAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			MCharacter = Cast<AMedusaCharacter>(Pawn);
		}
	}
}

void UMeduseAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			MCharacter = Cast<AMedusaCharacter>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
	}
}


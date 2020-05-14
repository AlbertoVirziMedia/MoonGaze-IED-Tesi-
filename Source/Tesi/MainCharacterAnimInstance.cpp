// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h"
#include "MainTargetSystemComponent.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			MainCharacter = Cast<AMainCharacter>(Pawn);

		}
	}

	if (Pawn)
	{

		//Main Target System Reference
		MainTargetSystem = Pawn->FindComponentByClass<UMainTargetSystemComponent>();

		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = Speed.Size();
		VerticalSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (MainTargetSystem)
		{
			bIsInTarget = MainTargetSystem->TargetLocked;
		}
		

		if (MainCharacter == nullptr)
		{
			MainCharacter = Cast<AMainCharacter>(Pawn);
		}
	}
}

void UMainCharacterAnimInstance::Attack()
{
	if (CombatMontage)
	{
		//Determines which section is currently playing
		FName CurrentSection = Montage_GetCurrentSection(CombatMontage);

		if (CurrentSection.IsNone())
		{
			Montage_Play(CombatMontage, 2.f);
		}
		else if (CurrentSection.IsEqual("FirstAttack") && bAcceptSecondAttack)
		{
			Montage_JumpToSection(FName("SecondAttack"), CombatMontage);
			bAcceptSecondAttack = false;
		}

	}
}

void UMainCharacterAnimInstance::Blocking()
{
	BlockingAnimRate = 0.f;

	if (CombatMontage)
	{
		Montage_Play(CombatMontage, BlockingAnimRate);
		Montage_JumpToSection(FName("Blocking"), CombatMontage);
	}
}

void UMainCharacterAnimInstance::BlockEnd()
{
	BlockingAnimRate = 1.f;

	if (CombatMontage)
	{
		Montage_Play(CombatMontage, BlockingAnimRate);
		Montage_JumpToSection(FName("Blocking"), CombatMontage);
	}
}
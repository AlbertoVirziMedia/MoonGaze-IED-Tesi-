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

	bIsBlocking = false;
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

		/**/
		/*Get Right and Forward velocity for OnTarget Blendspace
		/**/
//		RightVector = Pawn->GetActorRightVector();
//		ForwardVector = Pawn->GetActorForwardVector();
		RightVector = Pawn->FindComponentByClass<USkeletalMeshComponent>()->GetRightVector();
		ForwardVector = Pawn->FindComponentByClass<USkeletalMeshComponent>()->GetForwardVector();

		MainCharacterRightVelocity = (FVector::DotProduct(RightVector, Speed) * MovementSpeed);
		MainCharacterForwardVelocity = (FVector::DotProduct(ForwardVector, Speed) * MovementSpeed);

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
			Montage_Play(CombatMontage, 1.f);
			Montage_JumpToSection(FName("FirstAttack"), CombatMontage);
		}
		else if (CurrentSection.IsEqual("FirstAttack") && bAcceptSecondAttack)
		{
			Montage_JumpToSection(FName("SecondAttack"), CombatMontage);
			bAcceptSecondAttack = false;
			MainCharacter->FinalSmashAttack();
		}
/*		else if (CurrentSection.IsEqual("SecondAttack") && bAcceptThirdAttack)
		{
			Montage_JumpToSection(FName("ThirdAttack"), CombatMontage);
			bAcceptThirdAttack = false;
		}
		else if (CurrentSection.IsEqual("ThirdAttack") && bAcceptFourthAttack)
		{
			Montage_JumpToSection(FName("FourthAttack"), CombatMontage);
			bAcceptFourthAttack = false;
		}
*/		
	}
}

void UMainCharacterAnimInstance::Damage()
{
	if (CombatMontage)
	{
		Montage_Play(CombatMontage, 1.f);
		Montage_JumpToSection(FName("Damage"), CombatMontage);
	}
}

void UMainCharacterAnimInstance::Blocking()
{
	if (CombatMontage)
	{
		Montage_Play(CombatMontage, 1.f);
		Montage_JumpToSection(FName("Block"), CombatMontage);
		bIsBlocking = true;
	}
}

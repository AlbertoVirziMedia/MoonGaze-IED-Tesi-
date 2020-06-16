
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/**/
	/*Character AnimInstance Movement Variables
	/**/
	//Variable Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float VerticalSpeed;

	//Right Vector
	FVector RightVector;
	//Forward Vector
	FVector ForwardVector;

	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MainCharacterRightVelocity;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MainCharacterForwardVelocity;


	//Bool that check if the player is in air
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;
	//Reference to the pawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;
	//Reference to the character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AMainCharacter* MainCharacter;

	//Reference to the MainTargetSystem
	class UMainTargetSystemComponent* MainTargetSystem;

	//Bool is in target
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInTarget;

	/**/
	/*Character AnimInstance Attack Variables
	/**/
	//Reference to the AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* CombatMontage;
	//bool that check if player can do second attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAcceptSecondAttack;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAcceptThirdAttack;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAcceptFourthAttack;

	/**/
	/*Character AnimInstance Movement Function
	/**/
	// Initialization of the AnimInstance
	virtual void NativeInitializeAnimation() override;
	// Update every frame the Animation
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	/**/
	/*Character AnimInstance Attack Variables
	/**/
	//Determines which attack animation will be played
	void Attack();
	void Damage();

	/**/
	/*Character AnimInstance Blocking Variables
	/**/
	//Float that change the anim rate of the blocking animation
	float BlockingAnimRate;
	//
	void Blocking();
	//
	void BlockEnd();

	
};

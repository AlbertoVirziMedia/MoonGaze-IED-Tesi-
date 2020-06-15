// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EsploratoriMeleeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API UEsploratoriMeleeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/**/
	/*AnimInstance Variables
	/**/
	//Movement Speed of the Character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;
	//Reference to the pawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;
	//Reference to the Esploratori Melee Character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AEsploratoriMeleeCharacter* EMCharacter;

	/**/
	/*Character AnimInstance Attack Variables
	/**/
	//Reference to the AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* EMCombatMontage;



	/**/
	/*AnimInstance Functions
	/**/
	//Native Initialization Animation override
	virtual void NativeInitializeAnimation() override;
	//Update animation function override
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();
	//
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void TakeDamageAnim();
	
	
};

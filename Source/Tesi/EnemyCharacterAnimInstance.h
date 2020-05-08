// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API UEnemyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/**/
	/*AnimInstance Variables
	/**/
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AEnemyCharacter* Enemy;

	/**/
	/*AnimInstance Functions
	/**/
	//
	virtual void NativeInitializeAnimation() override;
	//
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EsploratoriMeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AEsploratoriMeleeAIController : public AAIController
{
	GENERATED_BODY()

	AEsploratoriMeleeAIController();

public:

	/**/
	/*Only Variables
	/**/

	//AI Perception
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComp;

	/**/
	/*IA Behavior Variables
	/**/
	//Blackboard Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA")
	class UBlackboardComponent* EMBlackboardComp;
	//BehaviorTree Reference
	UPROPERTY(transient)
	class UBehaviorTreeComponent* EMBehaviorTreeComp;

	//Anim Montage Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerAbility")
	bool bCanTakeDamage;
	//Time to give to the TakeDamageTimer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	float DashStop;
	//TakeDamageTimer
	UPROPERTY()
	FTimerHandle DashHandle;


public:

	/**/
	/*IA functions
	/**/

	//Override of the OnPossess function
	virtual void OnPossess(APawn* InPawn) override;

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return EMBlackboardComp; };

	/**/
	/*IA Sight Function
	/**/


};

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

public:

	AEsploratoriMeleeAIController();

	/**/
	/*Only Variables
	/**/

	/**/
	/*IA Behavior Variables
	/**/
	//Blackboard Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA")
	class UBlackboardComponent* EMBlackboardComp;
	//BehaviorTree Reference
	UPROPERTY(transient)
	class UBehaviorTreeComponent* EMBehaviorTreeComp;


public:

	/**/
	/*IA functions
	/**/

	//Override of the OnPossess function
	virtual void OnPossess(APawn* InPawn) override;

	void StopTree();

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return EMBlackboardComp; };

};

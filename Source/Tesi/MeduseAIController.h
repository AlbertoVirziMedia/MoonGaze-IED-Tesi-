// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MeduseAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AMeduseAIController : public AAIController
{
	GENERATED_BODY()

public:

	AMeduseAIController();

	/**/
	/*Only Variables
	/**/

	/**/
	/*IA Behavior Variables
	/**/
	//Blackboard Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA")
	class UBlackboardComponent* MBlackboardComp;
	//BehaviorTree Reference
	UPROPERTY(transient)
	class UBehaviorTreeComponent* MBehaviorTreeComp;

public:

	/**/
	/*IA functions
	/**/

	//Override of the OnPossess function
	virtual void OnPossess(APawn* InPawn) override;

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return MBlackboardComp; };
	
};

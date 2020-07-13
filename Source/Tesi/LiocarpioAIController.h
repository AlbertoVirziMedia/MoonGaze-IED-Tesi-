// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LiocarpioAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API ALiocarpioAIController : public AAIController
{
	GENERATED_BODY()

public:

	ALiocarpioAIController();

	/**/
	/*Only Variables
	/**/
	class ALiocarpioCharacter* LCharacter;
	bool LIsAlive;
	/**/
	/*IA Behavior Variables
	/**/
	//Blackboard Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA")
	class UBlackboardComponent* LBlackboardComp;
	//BehaviorTree Reference
	UPROPERTY(transient)
	class UBehaviorTreeComponent* LBehaviorTreeComp;


public:

	/**/
	/*IA functions
	/**/

	//Override of the OnPossess function
	virtual void OnPossess(APawn* InPawn) override;

	//
	virtual void Tick(float DeltaTime) override;

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return LBlackboardComp; };

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TESI_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyAIController();

	/**/
	/*Only Variables
	/**/
	//BehaviorTreeComponent
	UBehaviorTreeComponent*BehaviorComp;
	/**/
	/*Blackboards
	/**/
	//Reference to the Blackboards
	UBlackboardComponent* BlackboardComp;
	//Blackboard keys
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName LocationToGoKey;

	//Array that contain every position
	TArray<AActor*> BotTargetPoints;

private:


public:

	/**/
	/*Only Functions
	/**/
	//Possesion function (Initialize the Blackboard and start the Behavior tree)
	virtual void OnPossess(APawn* Pawn) override;

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };

	//Get poits to move
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoits() { return BotTargetPoints; };


};

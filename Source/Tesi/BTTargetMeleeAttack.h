// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTargetMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API UBTTargetMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	//Result of the execution of the node (Succesful or failed)
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};

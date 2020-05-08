// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTargetPointSelection.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API UBTTargetPointSelection : public UBTTaskNode
{
	GENERATED_BODY()

public:

	/**/
	/*IA Point Selector
	/**/
	virtual EBTNodeResult::Type
	ExecuteTask(UBehaviorTreeComponent&OwnerComp, uint8* NodeMemory) override;
	
};

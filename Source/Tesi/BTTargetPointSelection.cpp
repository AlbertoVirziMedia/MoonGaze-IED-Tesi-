// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTargetPointSelection.h"
#include "BotTargetPoint.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type
UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	//If the Controller is valid
	//Get the Blackboard Component and the current point of the bot
	//Search for the next point
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoits();

		//This variable will contain a a random index for the next possible point
		int32 RandomIndex;

		//Here we store the possible next target point
		ABotTargetPoint* NextTargetPoint = nullptr;

		//Find the next point, different from the current one
		do 
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			//
			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);
		} 
		while (CurrentPoint == NextTargetPoint);

		//Update the next location in the blackboard
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		//
		return EBTNodeResult::Succeeded;
	}

	//
	return EBTNodeResult::Failed;
}


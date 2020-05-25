// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTargetMeleeAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EsploratoriMeleeAIController.h"
#include "EsploratoriMeleeCharacter.h"
#include "MainCharacter.h"

EBTNodeResult::Type UBTTargetMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEsploratoriMeleeAIController* EMAIController = Cast<AEsploratoriMeleeAIController>(OwnerComp.GetAIOwner());

	AEsploratoriMeleeCharacter* EMCharacter = Cast<AEsploratoriMeleeCharacter>(OwnerComp.GetOwner());

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EMAIController->EnemyKeyID));

	UE_LOG(LogTemp, Warning, TEXT("Attack"));



	return EBTNodeResult::Succeeded;
}
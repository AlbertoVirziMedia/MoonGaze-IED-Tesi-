// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EsploratoriMeleeCharacter.h"

AEsploratoriMeleeAIController::AEsploratoriMeleeAIController()
{
	//Create Reference to BlackBoard
	EMBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("EMBlackboardComp"));
	//Create Reference to BehaviourTree
	EMBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("EMBehaviorTreeComp"));

}

void AEsploratoriMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Cast EnemyRangeCharacter and check if it's my own EnemyAiCharacter
	AEsploratoriMeleeCharacter* EMCharacter = Cast<AEsploratoriMeleeCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (EMCharacter && EMCharacter->CharacterBehaviorTree)
	{
		EMBlackboardComp->InitializeBlackboard(*(EMCharacter->CharacterBehaviorTree->BlackboardAsset));

		EnemyKeyID = EMBlackboardComp->GetKeyID("Target");

		EnemyState = EMBlackboardComp->GetKeyID("EnemyAiState");

		EMBehaviorTreeComp->StartTree(*EMCharacter->CharacterBehaviorTree);

		EMBlackboardComp->SetValue<UBlackboardKeyType_Int>(EnemyState, 0);
	}
}

void AEsploratoriMeleeAIController::SetSeenTarget(APawn* MainCharacterSeen)
{
	//Registers the Pawn that the AI has seen in the blackboard
	if (EMBlackboardComp)
	{
		GLog->Log("EnemyState");
		EMBlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, MainCharacterSeen);
		EMBlackboardComp->SetValue<UBlackboardKeyType_Int>(EnemyState, 1);
	}

}

void  AEsploratoriMeleeAIController::SetSensedTarget(APawn* MainCharacterHeard)
{
	//Registers the Pawn that the AI has hear in the blackboard
	if (EMBlackboardComp)
	{
		EMBlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, MainCharacterHeard);
		EMBlackboardComp->SetValue<UBlackboardKeyType_Int>(EnemyState, 1);
	}

}

void AEsploratoriMeleeAIController::ChangeBoolIsInZoneOfCombat()
{
	//Registers the Pawn that the AI has hear in the blackboard
	if (EMBlackboardComp)
	{
		EMBlackboardComp->SetValue<UBlackboardKeyType_Int>(EnemyState, 2);
	}
}
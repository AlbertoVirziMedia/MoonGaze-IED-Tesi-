// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriRangeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EsploratoriRangeCharacter.h"

AEsploratoriRangeAIController::AEsploratoriRangeAIController()
{

	//Create Reference to BlackBoard
	ERBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("ERBlackboardComp"));
	//Create Reference to BehaviourTree
	ERBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("ERBehaviorTreeComp"));

}

void AEsploratoriRangeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Cast EnemyRangeCharacter and check if it's my own EnemyAiCharacter
	AEsploratoriRangeCharacter* ERCharacter = Cast<AEsploratoriRangeCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (ERCharacter && ERCharacter->CharacterBehaviorTree)
	{
		//Initialize the Blackboard
		ERBlackboardComp->InitializeBlackboard(*(ERCharacter->CharacterBehaviorTree->BlackboardAsset));

		ERBehaviorTreeComp->StartTree(*ERCharacter->CharacterBehaviorTree);
	}
}

void AEsploratoriRangeAIController::StopTree()
{
	ERBehaviorTreeComp->Deactivate();
	ERBehaviorTreeComp->StopTree();
}


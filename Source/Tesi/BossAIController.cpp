// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossCharacter.h"

ABossAIController::ABossAIController()
{

	//Create Reference to BlackBoard
	BossBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BossBlackboardComp"));
	//Create Reference to BehaviourTree
	BossBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BossBehaviorTreeComp"));

}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Cast EnemyRangeCharacter and check if it's my own EnemyAiCharacter
	ABossCharacter* BossCharacter = Cast<ABossCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (BossCharacter && BossCharacter->CharacterBehaviorTree)
	{
		//Initialize the Blackboard
		BossBlackboardComp->InitializeBlackboard(*(BossCharacter->CharacterBehaviorTree->BlackboardAsset));

		BossBehaviorTreeComp->StartTree(*BossCharacter->CharacterBehaviorTree);
	}
}

void ABossAIController::StopTree()
{
	BossBehaviorTreeComp->Deactivate();
	BossBehaviorTreeComp->StopTree();
}

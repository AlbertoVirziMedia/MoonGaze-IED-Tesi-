// Fill out your copyright notice in the Description page of Project Settings.


#include "EsploratoriMeleeAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EsploratoriMeleeCharacter.h"

AEsploratoriMeleeAIController::AEsploratoriMeleeAIController()
{
	//AI Perception Comp that update every frame what Enmies see
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	//OnUpdatefunction of this component is in BP

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
		//Initialize the Blackboard
		EMBlackboardComp->InitializeBlackboard(*(EMCharacter->CharacterBehaviorTree->BlackboardAsset));

		EMBehaviorTreeComp->StartTree(*EMCharacter->CharacterBehaviorTree);
	}
}

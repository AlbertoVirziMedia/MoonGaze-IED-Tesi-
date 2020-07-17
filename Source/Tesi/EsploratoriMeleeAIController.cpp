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

	//Cast EnemyMeleeCharacter and check if it's my own EnemyAiCharacter
	AEsploratoriMeleeCharacter* EMCharacter = Cast<AEsploratoriMeleeCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (EMCharacter && EMCharacter->CharacterBehaviorTree)
	{
		//Initialize the Blackboard
		EMBlackboardComp->InitializeBlackboard(*(EMCharacter->CharacterBehaviorTree->BlackboardAsset));

		EMBehaviorTreeComp->StartTree(*EMCharacter->CharacterBehaviorTree);
	}
}

void AEsploratoriMeleeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EMCharacter)
	{
		EMIsAlive = EMCharacter->bEnemyIsAlive;
		if (!EMIsAlive)
		{
			EMBehaviorTreeComp->StopTree();
			GLog->Log("Dead")
		}
	}
}

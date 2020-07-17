// Fill out your copyright notice in the Description page of Project Settings.


#include "LiocarpioAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "LiocarpioCharacter.h"

ALiocarpioAIController::ALiocarpioAIController()
{

	//Create Reference to BlackBoard
	LBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("LBlackboardComp"));
	//Create Reference to BehaviourTree
	LBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("LBehaviorTreeComp"));

}

void ALiocarpioAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Cast EnemyRangeCharacter and check if it's my own EnemyAiCharacter
	ALiocarpioCharacter* LCharacter = Cast<ALiocarpioCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (LCharacter && LCharacter->CharacterBehaviorTree)
	{
		//Initialize the Blackboard
		LBlackboardComp->InitializeBlackboard(*(LCharacter->CharacterBehaviorTree->BlackboardAsset));

		LBehaviorTreeComp->StartTree(*LCharacter->CharacterBehaviorTree);
	}
}

void ALiocarpioAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (LCharacter)
	{
		LIsAlive = LCharacter->bEnemyIsAlive;
		if (!LIsAlive)
		{
			LBehaviorTreeComp->StopTree();	
		}
	}
}

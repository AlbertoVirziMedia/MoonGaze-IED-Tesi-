// Fill out your copyright notice in the Description page of Project Settings.


#include "MeduseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MedusaCharacter.h"

AMeduseAIController::AMeduseAIController()
{
	//Create Reference to BlackBoard
	MBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("EMBlackboardComp"));
	//Create Reference to BehaviourTree
	MBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("EMBehaviorTreeComp"));
}

void AMeduseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Cast EnemyRangeCharacter and check if it's my own EnemyAiCharacter
	AMedusaCharacter* MCharacter = Cast<AMedusaCharacter>(InPawn);

	//If ER is Enemy Character and he have the BehaviorTree
	if (MCharacter && MCharacter->CharacterBehaviorTree)
	{
		//Initialize the Blackboard
		MBlackboardComp->InitializeBlackboard(*(MCharacter->CharacterBehaviorTree->BlackboardAsset));

		MBehaviorTreeComp->StartTree(*MCharacter->CharacterBehaviorTree);
	}
}
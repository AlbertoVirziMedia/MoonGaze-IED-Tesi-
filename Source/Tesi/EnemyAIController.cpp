// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BotTargetPoint.h"
#include "EnemyAiPatrol.h"
#include "Kismet/GameplayStatics.h"

//Constructor
AEnemyAIController::AEnemyAIController()
{

	//Initialize the BehaviourTreeComponent, BlackboardCOmponent and the corresponding key
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";

}

//Override of the Unreal Possesses function 
void AEnemyAIController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	//Get the possessed character and check if it's my own EnemyAiCharacter
	AEnemyAiPatrol* AIChar = Cast<AEnemyAiPatrol>(Pawn);

	if (AIChar)
	{
		//if the blackboard is valid, initialize the blackboard for the corresponding behavior tree
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}

		//Populate the array of available bot target points
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);

		//Start the behavior tree which corresponds to the specific character
		BehaviorComp->StartTree(*AIChar->BehaviorTree);
	}
}
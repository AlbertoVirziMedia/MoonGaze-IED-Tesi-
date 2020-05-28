// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EsploratoriMeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AEsploratoriMeleeAIController : public AAIController
{
	GENERATED_BODY()

	AEsploratoriMeleeAIController();

public:

	/**/
	/*Only Variables
	/**/

	//AI Perception
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComp;

	/**/
	/*IA Behavior Variables
	/**/
	//Blackboard Reference
	UPROPERTY(transient)
	class UBlackboardComponent* EMBlackboardComp;
	//BehaviorTree Reference
	UPROPERTY(transient)
	class UBehaviorTreeComponent* EMBehaviorTreeComp;

	//Reference To The Esploratori Melee Blackboard key
	//Reference to the MainCharacter ID 
	uint8 EnemyKeyID;
	//Reference to the EnemyState ID
	uint8 EnemyState;

public:

	/**/
	/*IA functions
	/**/

	//Override of the OnPossess function
	virtual void OnPossess(APawn* InPawn) override;

	//Get Blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return EMBlackboardComp; };

	/**/
	/*IA Sight Function
	/**/
	/*Sets the sensed target in the blackboard*/
//	UFUNCTION(BlueprintCallable)
//	void SetSeenTarget(APawn* MainCharacterSeen);

	/**/
	/*IA Hearing Function
	/**/
	/*Sets the new sensed target value inside our Blackboard values*/
//	UFUNCTION(BlueprintCallable)
//	void SetSensedTarget(APawn* MainCharacterHeard);

	/**/
	/*IA Combat Function
	/**/
	UFUNCTION(BlueprintCallable)
	void ChangeBoolIsInZoneOfCombat();

};

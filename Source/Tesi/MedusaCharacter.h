// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericEnemyCharacter.h"
#include "MedusaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AMedusaCharacter : public AGenericEnemyCharacter
{
	GENERATED_BODY()

public:

	AMedusaCharacter();

	/**/
	/*IA Variables
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AMeduseAIController* AIController;
	//bool that check when the enemy his hitten
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsGettingDameged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**/
	/*Combat Functions
	/**/
	// Function Called when enemy sight spot the Main Character
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	/**/
	/*Death Functions
	/**/
	//Function called when enemy die
	void Die();
	//function called at the end of the dead animation
	void DeadEnd();
	// Function that Destroy the Enemy Istance
	void Disappear();
};

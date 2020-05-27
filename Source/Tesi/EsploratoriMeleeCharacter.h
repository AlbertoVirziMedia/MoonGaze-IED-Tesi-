// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericEnemyCharacter.h"
#include "EsploratoriMeleeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AEsploratoriMeleeCharacter : public AGenericEnemyCharacter
{
	GENERATED_BODY()

public:

	AEsploratoriMeleeCharacter();

	/**/
	/*IA Variables
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AEsploratoriMeleeAIController* AIController;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**/
	/*Only Functions
	/**/

	/**/
	/*IA Sight Functions
	/**/
	// Function Called when enemy sight spot the Main Character
	UFUNCTION(BlueprintCallable, Category = "AI | Sight")
	virtual void OnSeePlayer(APawn* Pawn);
	/**/
	/*IA SoundListener Functions
	/**/
	/*Hearing function - will be executed when we hear a Pawn*/
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	/**/
	/*Component Collision Functions
	/**/
	//
	UFUNCTION()
	void OnZoneOfCombatBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//
	UFUNCTION()
	void OnZoneOfCombatEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//
	UFUNCTION()
	void DamageColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//
	UFUNCTION()
	void DamageColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**/
	/*Attack Functions
	/**/
	void MeleeAttack();
	void MeleeAttackEnd();
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

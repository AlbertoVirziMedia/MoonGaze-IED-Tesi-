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
	//bool that check when the enemy his hitten
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsGettingDameged;

	//AnimInstance Ref
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	class UEsploratoriMeleeAnimInstance* EMAnimInstance;
	//Reference to the Combat Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UAnimMontage* EMCombatMontage;

	//Anim Montage Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TakeDamageAnim")
	bool bCanTakeDamage;
	//Time to give to the TakeDamageTimer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TakeDamageAnim")
	float TakeDamageStop;
	//TakeDamageTimer
	UPROPERTY()
	FTimerHandle TakeDamageHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**/
	/*Only Functions
	/**/

	/**/
	/*Combat Functions
	/**/
	// Function Called when enemy sight spot the Main Character
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	//
	UFUNCTION()
	void ResetTakeDamage();

	/**/
	/*Component Collision Functions
	/**/
	//
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

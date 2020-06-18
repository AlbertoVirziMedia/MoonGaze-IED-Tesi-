// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericEnemyCharacter.generated.h"

UCLASS()
class TESI_API AGenericEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenericEnemyCharacter();

	/**/
	/*Only Variables
	/**/
	//Enemy Character position in the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	FVector EnemyPosition;


	//BehaviourTree Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* CharacterBehaviorTree;


	/**/
	/*IA Sight/Hearing Variables
	/**/
	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	/**/
	/*Stats Variables
	/**/
	//Max Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth;
	//Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;
	//bool that check if the enemy is alive
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bEnemyIsAlive;

	/**/
	/*Combat Variables
	/**/
	//Damage Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	class UBoxComponent* DamageCollider;
	//Enemy Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage;
	//Bool when the enemy is attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAttacking;
	//Adding delay between attack/ Timer
	FTimerHandle AttackTimerHandle;
	//Adding delay between attack/ Min Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackMinTime;
	//Adding delay between attack / Max Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackMaxTime;
	//Type of Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<UDamageType> EnemyDamageTypeClass;

	/**/
	/*Combat AParticle Variables
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat | Particle")
	class UParticleSystemComponent* DamagedParticle;

	/**/
	/*Combat Animations Variables
	/**/
	//Reference to combat Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation | Combat")
	class UAnimMontage* EnemyCombatMontage;

	/**/
	/*Death Variables
	/**/
	//Timer after death to destroy enemy object
	FTimerHandle DestroyObjectTimer;
	//Time to give to the timer destroy object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	float DestroyObjectDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**/
	/*TakeDamage Functions override
	/**/
	//Enemy Take Damage function
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

};

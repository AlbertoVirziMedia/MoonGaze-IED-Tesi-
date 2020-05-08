// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_MoveToTarget UMETA(DisplayName = "MoveToTarget"),
	EMS_Attacking UMETA(DisplayName = "Attacking"),
	EMS_Dead UMETA(DisplayName = "Dead"),

	EMS_Max UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class TESI_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AEnemyCharacter();

	/**/
	/*Only Variables
	/**/

	/**/
	/*Enemy Movement Status
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	EEnemyMovementStatus EnemyMovementStatus;

	/**/
	/*IA Variables
	/**/
	//Reference to the Agrosphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class USphereComponent* AgroSphere;
	//Reference to the CombatSphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class USphereComponent* CombatSphere;
	//Reference to the Controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AAIController* AIController;
	//Bool that check if the Character is in CombatZone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bOverlappingCombatSphere;
	//Reference to the MainCharacter
	class AMainCharacter* CombatTarget;
	//Bool that change when Main Die
	bool bHasValidTarget;

	/**/
	/*Enemy Stats Variables
	/**/
	//Max Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	float MaxHealth;
	//Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	float Health;
	//bool that check if the enemy is alive
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyStats")
	bool bEnemyIsAlive;
	//Enemy Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	float Damage;

	/**/
	/*Combat Effect
	/**/
	//Particle when Damaged
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UParticleSystem* HitParticle;

	/**/
	/*Combat Variables
	/**/
	//Damage Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	class UBoxComponent* DamageCollider;
	//Reference to combat Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UAnimMontage* EnemyCombatMontage;
	//Bool when the enemy is attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAttacking;
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
	/*Death Variables
	/**/
	//Death Timer (Time to destroy the enemy object after the death)
	FTimerHandle DeathTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DeathDelay;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**/
	/*Only Functions
	/**/

	/**/
	/*Enemy Movement Status Enum Function
	/**/
	//Get Enemy Movement Status
	FORCEINLINE void SetEnemyMovementStatus(EEnemyMovementStatus Status) { EnemyMovementStatus = Status; }
	//Set Enemy Movement Status
	FORCEINLINE EEnemyMovementStatus GetEnemyMovementStatus() { return EnemyMovementStatus; }

	/**/
	/*Agro Sphere Functions
	/**/
	//AgroSphere Overlap Function
	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//MovementFunction
	UFUNCTION(BlueprintCallable)
	void MoveToTarget(class AMainCharacter* Target);

	/**/
	/*Combat Sphere Functions
	/**/
	UFUNCTION()
	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**/
	/*Combat Functions
	/**/
	//Function to play CombatMontage
	UFUNCTION(BlueprintCallable)
	void Attack();
	//Function called at the end of the attack
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	//Activate AttackCollider
	UFUNCTION(BlueprintCallable)
	void ActivateCollision();
	//DeactivateCollision
	UFUNCTION(BlueprintCallable)
	void DeactivateCollision();
	//
	void DamageColliderOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//
	void DamageColliderOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//Enemy Take Damage function
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/**/
	/*Death Functions
	/**/
	//Function called when enemy die
	void Die();
	//function called at the end of the dead animation
	UFUNCTION(BlueprintCallable)
	void DeadEnd();
	// Function that Destroy the Enemy Istance
	void Disappear();

};

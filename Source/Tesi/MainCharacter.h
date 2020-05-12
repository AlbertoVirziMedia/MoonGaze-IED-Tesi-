// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class TESI_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AMainCharacter();

	/**/
	/*Only Variables
	/**/

	/**/
	/*Camera Variables
	/**/
	//Reference to Camera Boom (SpringArm Component)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;
	//Reference to Follow Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;
	//Turn Rate for the Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;
	//Up/Down Rate for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	/**/
	/*Character Movement
	/**/
	//Character Rotation Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float CharacterRotationRate;
	//Double Jump Counter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	int DoubleJumpCounter;
	//Jump height of the second jump
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpHeight;

	/**/
	/*Main Character Ability
	/**/
	/**/
	/*Dash
	/**/
	//Dash Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	float DashDistance;
	//Dash Duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	float DashDuration;
	//bool that check if the player can dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	bool CanDash;
	//bool that check if the player is dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	bool IsDashing;
	//Time to give to the DashTimer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAbility")
	float DashStop;
	//DashTimer
	UPROPERTY()
	FTimerHandle DashHandle;

	/**/
	/*Character Stats
	/**/
	//Max Health
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float MaxHealth;
	//Health at the Moment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Health;
	//Bool that check if PlayerCharacter is alive
	bool bIsAlive;
	//Player Max speed 
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
	float RunningSpeed;

	/**/
	/*Main Character Player Component Reference (HUD)
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	class AMainCharacterPlayerController* MainCharacterPlayerController;

	/**/
	/*Reference to the Enemy
	/**/
	//Reference to the Enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemyCharacter* CombatTarget;
	//bool that check if Enemy have a CombatTarget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasEnemyCombatTarget;

	/**/
	/*Player Weapon
	/**/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat | Weapons")
	class AWeapon* EquippedWeapon;

	/**/
	/*Player Combat
	/**/
	//Reference to the Combat Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UAnimMontage* CombatMontage;
	//bool that check if attack button is pressed
	bool bAttackButtonDown;

	/**/
	/*Player Combat Collider
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat | BP")
	class UBoxComponent* SwordAttack;

	/**/
	/*Player Combat Blocking
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat | Blocking")
	bool bIsBlocking;

	/**/
	/*Player Combat Effect
	/**/
	//HitParticle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticle;

	/**/
	/*Camera Shake
	/**/
	//Set the SubClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Shake")
	TSubclassOf<UCameraShake> CameraJumpShake;

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy Distance")
	class AEnemyCharacter* EnemyTargetRefToDistance;


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
	/*Camera Functions
	/**/
	//Camera Function
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	//Turning at Rate Function
	UFUNCTION()
	void TurnAtRate(float Rate);
	//Up/Down at Rate Function
	UFUNCTION()
	void LookUpAtRate(float Rate);

	/**/
	/*Player Stats Functions
	/**/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	void Die();
	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	/**/
	/*CharacterMovement Functions
	/**/
	//Move Forward/Backward function
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);
	//Move Right/Left function
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);
	//Override of the Unreal Jump function
	virtual void Jump() override;
	//Double Jump Function
	UFUNCTION(BlueprintCallable)
	void DoubleJump();
	//Override Unreal Landed Function in order to add camera shake
	UFUNCTION(BlueprintCallable)
	virtual void Landed(const FHitResult& Hit);

	/**/
	/*CharacterMovement Ability Functions
	/**/

	/**/
	/*Dash
	/**/
	//Function called for dashing
	UFUNCTION(BlueprintCallable, Category = "Player Ability")
	void Dash();
	//Function called for stop the dash
	UFUNCTION(BlueprintCallable, Category = "Player Ability")
	void StopDashing();
	//Function called that reset the dash
	UFUNCTION()
	void ResetDash();

	/**/
	/*Weapon Equipment Functions
	/**/
	//Set the equipped weapon
	void SetEquippedWeapon(AWeapon* WeaponToSet);
	//Return the equipped weapon
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }

	/**/
	/*Attack Functions 
	/**/
	//Attack Function
	UFUNCTION(BlueprintCallable)
	void Attack();
	//Attack End Function
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	/**/
	/*BLocking Functions
	/**/
	//Function Called on block
	UFUNCTION(BlueprintCallable)
	void Blocking();
	//Function called on Block end
	UFUNCTION(BlueprintCallable)
	void BlockEnd();

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Engine.h"
#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Public/TimerManager.h"
#include "MainCharacterPlayerController.h"
#include "Weapon.h"
#include "MainCharacterAnimInstance.h"
#include "EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainCharacterCameraShake.h"
#include "MainTargetSystemComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**/
	/*Camera Settings
	/**/
	//Create SpingArm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//Attach CameraBoom
	CameraBoom->SetupAttachment(GetRootComponent());
	//Set the Camera Distance
	CameraBoom->TargetArmLength = 600.f;
	//Set the Spring Arm controller
	CameraBoom->bUsePawnControlRotation = true;
	//Camera Lag
	CameraBoom->bEnableCameraLag;
	//Create Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//Attach FollowCamera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//Set the Camera controller
	FollowCamera->bUsePawnControlRotation = false;
	//Turn Rate Value
	BaseTurnRate = 65.f;
	//Up/Down Rate Value
	BaseLookUpRate = 65.f;

	/**/
	/*Character Movement Settings
	/**/
	//Setting the Character Rotation variables
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	//Configure Character Rotation 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//Set the Character Rotation Rate
	CharacterRotationRate = 650.f;
	//Setting Character Movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, CharacterRotationRate, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	//
	DoubleJumpCounter = 0;
	//Second Jump Height
	JumpHeight = 600.f;

	/**/
	/*Character Ability Settings
	/**/
	//Set Dash Distance
	DashDistance = 6000.f;
	//Set Dash Duration
	DashDuration = 1.f;
	//Set bool canDash 
	CanDash = true;
	//Set bool IsDashing 
	IsDashing = false;
	//Set When dash stop
	DashStop = 0.1f;

	/**/
	/*Character Damage Collider
	/**/
	GetCapsuleComponent()->SetCapsuleSize(45.f, 95.f);

	/**/
	/*Character Stats
	/**/
	//Max Health
	MaxHealth = 100.f;
	//Every Frame Health
	Health = 100.f;
	//Bool that check if PlayerCharacter is alive
	bIsAlive = true;
	//Max Speed
	RunningSpeed = 650.f;

	/**/
	/*Attack Settings
	/**/
	//Set attack button down bool
	bAttackButtonDown = false;

	/**/
	/*Attack Settings
	/**/
	bIsAttacking = false;

	/**/
	/*Attack Settings Blocking
	/**/
	//Bool That check if the player is blocking
	bIsBlocking = false;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*Set Main Player Controller (HUD)
	/**/
	MainCharacterPlayerController = Cast<AMainCharacterPlayerController>(GetController());

	/**/
	/*Set Main Player Controller (HUD)
	/**/
	bHasEnemyCombatTarget = false;

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CombatTarget)
	{
		EnemyTargetRefToDistance = CombatTarget;
	}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	/**/
	/*Character Camera
	/**/
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);


	/**/
	/*Character Movement
	/**/
	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::DoubleJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/**/
	/*Character Ability
	/**/
	//Dash
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::Dash);

	/**/
	/*Attack
	/**/
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMainCharacter::AttackEnd);

	/**/
	/*Blocking
	/**/
	PlayerInputComponent->BindAction("Blocking", IE_Pressed, this, &AMainCharacter::Blocking);
	PlayerInputComponent->BindAction("Blocking", IE_Released, this, &AMainCharacter::BlockEnd);

}

//Turn at Rate Function
void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

//Look Up at Rate Function
void AMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


//Move Forward Function
void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		//const FRotator Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

//Move Right/Left Function
void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

//Override Jump Function
void AMainCharacter::Jump()
{
	if (bIsAlive)
	{
		Super::Jump();
	}
}

//DoubleJumpFunction
void AMainCharacter::DoubleJump()
{
	if (bIsAlive && !IsDashing)
	{
		if (DoubleJumpCounter <= 1)
		{
			ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
			DoubleJumpCounter++;
		}
	}	
}

//Override Unreal Landed Function
void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	DoubleJumpCounter = 0;
	MainCharacterPlayerController->PlayerCameraManager->PlayCameraShake(CameraJumpShake, 1.f);
}

//Dash Function
void AMainCharacter::Dash()
{
	if (CanDash)
	{
		FVector InputVector = GetLastMovementInputVector();
		if (InputVector == FVector(0,0,0))
		{
			InputVector = GetActorForwardVector();
		}
		LaunchCharacter(InputVector * DashDistance, true, true);
		CanDash = false;
		GetWorldTimerManager().SetTimer(DashHandle, this, &AMainCharacter::StopDashing, DashStop, false);
		IsDashing = true;
	}
}

//Stop Dash Function
void AMainCharacter::StopDashing()
{
	//
	GetCharacterMovement()->StopMovementImmediately();
	//
	GetWorldTimerManager().SetTimer(DashHandle, this, &AMainCharacter::ResetDash, DashDuration, false);
	//
	IsDashing = false;
}

//Reset Dash Function
void AMainCharacter::ResetDash()
{
	//After the timer end, Character can Dash
	CanDash = true;
}

//Set Equipped Weapon (This function is called in Weapon.cpp)
void AMainCharacter::SetEquippedWeapon(AWeapon* WeaponToSet)
{
	//Set the Equipped Weapon
	EquippedWeapon = WeaponToSet;
}

//Start the attack function
void AMainCharacter::Attack()
{
	//Set the attack button bool
	bAttackButtonDown = true;
	if (EquippedWeapon)
	{
//		EquippedWeapon->WeaponAttack();
	}
	//Reference to the main character anim instance
	UMainCharacterAnimInstance* MainCharacterAnimInstanceRef = Cast<UMainCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MainCharacterAnimInstanceRef)
	{
		//Call the Main Character Anim Instance Attack Function
		MainCharacterAnimInstanceRef->Attack();
	}
}

//End the attack function
void AMainCharacter::AttackEnd()
{
	bAttackButtonDown = false;
}

void AMainCharacter::Blocking()
{
	bIsBlocking = true;

	UMainCharacterAnimInstance* MainCharacterAnimInstanceRef = Cast<UMainCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MainCharacterAnimInstanceRef)
	{
		MainCharacterAnimInstanceRef->Blocking();
	}
}

void AMainCharacter::BlockEnd()
{
	bIsBlocking = false;

	UMainCharacterAnimInstance* MainCharacterAnimInstanceRef = Cast<UMainCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MainCharacterAnimInstanceRef)
	{
		MainCharacterAnimInstanceRef->BlockEnd();
	}
}

//This Function is Unreal function for TakeDamage
float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (!bIsBlocking)
	{
		if (Health - DamageAmount <= 0.f)
		{
			Health -= DamageAmount;
			Die();
			if (DamageCauser)
			{
				AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(DamageCauser);
				if (Enemy)
				{
					Enemy->bHasValidTarget = false;
				}
			}
		}
		else
		{
			Health -= DamageAmount;
		}
	}

	return DamageAmount;
}

//This Function is Called when Main->Health is =< 0
void AMainCharacter::Die()
{
	UAnimInstance* AnimIstance = GetMesh()->GetAnimInstance();
	if (AnimIstance && CombatMontage)
	{
		AnimIstance->Montage_Play(CombatMontage, 1.0f);
		AnimIstance->Montage_JumpToSection(FName("Death"));
	}
	bIsAlive = false;
}

//This Function is called at the end of the Dead Animation (In the MainAnim_BP)
void AMainCharacter::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
}

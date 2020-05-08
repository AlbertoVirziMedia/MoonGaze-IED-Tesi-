// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Classes/AIController.h"
#include "MainCharacter.h"
#include "MainCharacterPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**/
	/*Set Enemy Agro Sphere
	/**/
	//Create Agro Sphere
	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	//Setup The Attachment
	AgroSphere->SetupAttachment(GetRootComponent());
	//Set the Radius
	AgroSphere->InitSphereRadius(600.f);

	/**/
	/*Set Enemy Combat Sphere
	/**/
	//Create Combat Sphere
	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	//Setup the Attachment
	CombatSphere->SetupAttachment(GetRootComponent());
	//Set the Radius
	CombatSphere->InitSphereRadius(75.f);
	//Set the initial overlapping bool
	bOverlappingCombatSphere = false;

	/**/
	/*Set Enemy Initial Status
	/**/
	EnemyMovementStatus = EEnemyMovementStatus::EMS_Idle;

	/**/
	/*Set Enemy Stats
	/**/
	//Max Health
	MaxHealth = 100.f;
	//Current Health
	Health = 75.f;
	//Enemy is alive bool
	bEnemyIsAlive = true;
	//Enemy Damage
	Damage = 10.f;

	/**/
	/*Set Enemy Damage Collider
	/**/
	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollsion"));
	DamageCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("EnemySocket"));
	bAttacking = false;

	/**/
	/*Set Enemy Delay Between Attack
	/**/
	AttackMinTime = 0.5f;
	AttackMaxTime = 3.5f;

	/**/
	/*Set Enemy Destroy Variables
	/**/
	//Enemy Time to be Destroyed
	DeathDelay = 3.f;
	//Bool that change when Main Die
	bHasValidTarget = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/**/
	/*Cast the AIController
	/**/
	AIController = Cast<AAIController>(GetController());

	/**/
	/*AgroSphere Bind Actions
	/**/
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOnOverlapEnd);

	/**/
	/*CombatSphere Bind Actions
	/**/
	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::CombatSphereOnOverlapBegin);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::CombatSphereOnOverlapEnd);

	/**/
	/*Set the DamageCollider Overlapping channel
	/**/
	DamageCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	DamageCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DamageCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	DamageCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	/**/
	/*Set the DamageCollider Overlapping Bind
	/**/
	DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::DamageColliderOnOverlapBegin);
	DamageCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::DamageColliderOnOverlapEnd);

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Called when the player enter the Agrosphere
void AEnemyCharacter::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && bEnemyIsAlive)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			MoveToTarget(MainCharacter);
			MainCharacter->CombatTarget = this;
			MainCharacter->bHasEnemyCombatTarget = true;
			MainCharacter->MainCharacterPlayerController->DisplayEnemyHealthBar();
		}
	}
}

//Called when the enemy lose the target
void AEnemyCharacter::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			bHasValidTarget = false;
			SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Idle);
			if (AIController)
			{
				AIController->StopMovement();
				MainCharacter->CombatTarget = nullptr;
				MainCharacter->bHasEnemyCombatTarget = false;
				MainCharacter->MainCharacterPlayerController->RemoveEnemyHealthBar();
			}
		}
	}
}

//Move to target function
void AEnemyCharacter::MoveToTarget(class AMainCharacter* Target)
{
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_MoveToTarget);
	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController"));
		//Setting the Components for AIController
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(10.f);
		//Setting the NavPathSharedPtr
		FNavPathSharedPtr NavPath;
		//MoveTo Function
		AIController->MoveTo(MoveRequest, &NavPath);
	}
}

//Called when the Player enter in the CombatSphere
void AEnemyCharacter::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && bEnemyIsAlive)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			bHasValidTarget = true;
			CombatTarget = MainCharacter;
			bOverlappingCombatSphere = true;
			Attack();
		}
	}
}

//Called when the Player exit the CombatSphere
void AEnemyCharacter::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			if (MainCharacter->CombatTarget == this)
			{

			}
			bOverlappingCombatSphere = false;
			if (EnemyMovementStatus != EEnemyMovementStatus::EMS_Attacking)
			{
				MoveToTarget(MainCharacter);
				EnemyCombatMontage = nullptr;
			}
			GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		}
	}
}

//Called When MainCharacter enter in CombatSphere
void AEnemyCharacter::Attack()
{
	if (bEnemyIsAlive && bHasValidTarget)
	{
		if (AIController)
		{
			AIController->StopMovement();
			SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
		}
		if (!bAttacking)
		{
			bAttacking = true;
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				if (EnemyCombatMontage)
				{
					UE_LOG(LogTemp, Warning, TEXT("Attack"));
					AnimInstance->Montage_Play(EnemyCombatMontage, 1.f);
					AnimInstance->Montage_JumpToSection(FName("Attack"), EnemyCombatMontage);
				}
				
			}
		}
	}
}

//
void AEnemyCharacter::AttackEnd()
{
	bAttacking = false;
	if (bOverlappingCombatSphere)
	{
		float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::Attack, AttackTime);
	}
}

//
void AEnemyCharacter::DamageColliderOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageCollider"));
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			if (EnemyDamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(MainCharacter, Damage, AIController, this, EnemyDamageTypeClass);
			}
		}
	}
}

//
void AEnemyCharacter::DamageColliderOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

//
void AEnemyCharacter::ActivateCollision()
{
	DamageCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

//
void AEnemyCharacter::DeactivateCollision()
{
	DamageCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//Override of the Unreal Function
float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		Health -= DamageAmount;
		Die();
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}

//Function Called when enemy health is 0
void AEnemyCharacter::Die()
{
	UAnimInstance* AnimIstance = GetMesh()->GetAnimInstance();
	if (AnimIstance)
	{
		AnimIstance->Montage_Play(EnemyCombatMontage, 1.0f);
		AnimIstance->Montage_JumpToSection(FName("Death"), EnemyCombatMontage);
	}
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Dead);
	//Disable every collision for the enemy
	DamageCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AgroSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//Function called at the end of the death animation
void AEnemyCharacter::DeadEnd()
{
	//Stop the animation
	GetMesh()->bPauseAnims = true;
	//stop the skeletal update
	GetMesh()->bNoSkeletonUpdate = true;
	//Call the Destroy Function
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AEnemyCharacter::Disappear, DeathDelay);
}

//Function Called at the end of DeadEnd
void AEnemyCharacter::Disappear()
{
	Destroy();
}

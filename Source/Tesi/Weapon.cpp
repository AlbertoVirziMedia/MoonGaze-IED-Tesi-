// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "GenericEnemyCharacter.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**/
	/*Set the Skeletal Mesh
	/**/
	//Create the Skeletal Mesh 
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//Setup Attachment
	SkeletalMesh->SetupAttachment(GetRootComponent());

	/**/
	/*Set the CombatCollision
	/**/
	//Create the CombatCollision Box
	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	//Setup Attachment
	CombatCollision->SetupAttachment(GetRootComponent());

	/**/
	/*Set the Weapon Stats
	/**/
	//Set the Weapon Damage
	Damage = 25.f;


}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	/**/
	/*Set the Equip
	/**/
	ReferenceToMainCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MainCharacter = Cast<AMainCharacter>(ReferenceToMainCharacter);
	Equip(MainCharacter);

	/**/
	/*Set the Overlapping channel at the beginning
	/**/
/*	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
*/
	/**/
	/*Binding of the collision of the combat collider
	/**/
	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapEnd);
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//Equip Function
void AWeapon::Equip(class AMainCharacter* MainCharacter)
{
	if (MainCharacter)
	{	
		//Set the Istigator
		SetIstigator(MainCharacter->GetController());
		//Set collision response for the camera
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		//Set Physic simulation
		SkeletalMesh->SetSimulatePhysics(false);
		//Reference to the MainCharacter Socket
		const USkeletalMeshSocket* RightHandSocket = MainCharacter->GetMesh()->GetSocketByName("RightHandSocket");
		if (RightHandSocket)
		{
			//Attach the weapon to the socket
			RightHandSocket->AttachActor(this, MainCharacter->GetMesh());
			//Set as the equipped weapon
			MainCharacter->SetEquippedWeapon(this);
		}
	}
}

void AWeapon::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AGenericEnemyCharacter* Enemy = Cast<AGenericEnemyCharacter>(OtherActor);
		if (Enemy)
		{
/*			if (Enemy->HitParticle)
			{
				const USkeletalMeshSocket* WeaponSocket = SkeletalMesh->GetSocketByName("WeaponSocket");
				if (WeaponSocket)
				{
					FVector SocketLocation = WeaponSocket->GetSocketLocation(SkeletalMesh);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticle, SocketLocation, FRotator(0.f), false);
				}
			}
*/			
			if (WeaponDamageType)
			{
				UE_LOG(LogTemp, Warning, TEXT("WeaponDamageType"));
				UGameplayStatics::ApplyDamage(Enemy, Damage, WeaponInstigator, this, WeaponDamageType);
			}
		}
	}
}

void AWeapon::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWeapon::ActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UE_LOG(LogTemp, Warning, TEXT("ActivateCollsion"));
}

void AWeapon::EndCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogTemp, Warning, TEXT("EndCollsion"));
}

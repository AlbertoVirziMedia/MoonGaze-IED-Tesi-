// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TESI_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	/**/
	/*Only Variables
	/**/

	/**/
	/*Skeletal Mesh
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh;

	/**/
	/*Target for Equipment
	/**/
	//Reference to the MainCharacter
	class AMainCharacter* MainCharacter;
	class APawn* ReferenceToMainCharacter;

	/**/
	/*Weapon Stats
	/**/
	//Combat Collider
	//The Collider Logic is in Weapon BP


	//Weapon Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Combat")
	float Damage;
	//Class of DamageType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<UDamageType> WeaponDamageType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	AController* WeaponInstigator;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**/
	/*Weapon Functions
	/**/
	
	/**/
	/*Equipment Functions
	/**/
	//Function that Set the reference to the main
	void Equip(class AMainCharacter* MainCharacter);
	//Function To Set DamageOutput
	FORCEINLINE void SetIstigator(AController* Inst) { WeaponInstigator = Inst; };

	/**/
	/*CombatCollider Functions
	/**/
	UFUNCTION(BlueprintImplementableEvent)
	void WeaponAttack();


};

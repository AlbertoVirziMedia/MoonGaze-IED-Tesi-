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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Combat")
	class UBoxComponent* CombatCollision;
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
	//On Combat Collider Overlap Begin
	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//On Combat Collider Overlap End
	UFUNCTION()
	void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//This Functions are called in MainCharacterAnim_BP
	//The Function that Activate the Collider
	UFUNCTION(BlueprintCallable)
	void ActivateCollision();
	//The Function that Deactivate the Collider
	UFUNCTION(BlueprintCallable)
	void EndCollision();


};

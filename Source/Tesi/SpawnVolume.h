// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class TESI_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASpawnVolume();

	/**/
	/*Only Variables
	/**/

	/**/
	/*SpawningBox Stats
	/**/
	//Box for Spawning
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;
	//Class of Enemy to Spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> CharacterToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**/
	/*Only Functions
	/**/

	/**/
	/*Spawning Functions
	/**/
	//Function That Random select a spawn point
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawningPoint();
	//Function that Spawn the Character
	UFUNCTION()
	void SpawnOurPawn(UClass* ToSpawn, const FVector& Location);

};

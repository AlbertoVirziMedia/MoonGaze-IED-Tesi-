// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sea.generated.h"

UCLASS()
class TESI_API ASea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASea();

	/**/
	/*Static Mesh
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	class UStaticMeshComponent* StaticMesh;

	/**/
	/*Target for The Distance
	/**/
	//This is used by the sound designer
	//Reference to the MainCharacter
	class AMainCharacter* MainCharacter;
	class APawn* ReferenceToMainCharacter;

	/**/
	/*The Distance
	/**/
	float DistanceFromMainCharacter;
	float NormalizedDistanceFromMainCharacter;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**/
	/*Environmental Functions
	/**/
	//Calculate the distance between the MainCharacter and the Sea
	void CalculateDistanceFromTheMainCharacter(class AMainCharacter* ReferenceToTheMainCharacter);

};

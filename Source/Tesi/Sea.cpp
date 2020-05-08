// Fill out your copyright notice in the Description page of Project Settings.


#include "Sea.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASea::ASea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**/
	/*Static Mesh
	/**/
	//Create
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASea::BeginPlay()
{
	Super::BeginPlay();
	
	/**/
	/*Set the Reference
	/**/
	ReferenceToMainCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MainCharacter = Cast<AMainCharacter>(ReferenceToMainCharacter);
	
}

// Called every frame
void ASea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateDistanceFromTheMainCharacter(MainCharacter);
}

//
void ASea::CalculateDistanceFromTheMainCharacter(class AMainCharacter* ReferenceToTheMainCharacter)
{
	DistanceFromMainCharacter = UKismetMathLibrary::Abs(GetVerticalDistanceTo(ReferenceToTheMainCharacter));
	NormalizedDistanceFromMainCharacter = UKismetMathLibrary::NormalizeToRange(DistanceFromMainCharacter, 0.f, 100.f);
//	UE_LOG(LogTemp, Warning, TEXT("%d"), DistanceFromMainCharacter);
}


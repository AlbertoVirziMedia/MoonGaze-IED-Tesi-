// Fill out your copyright notice in the Description page of Project Settings.


#include "MedusaCharacter.h"
#include "MeduseAIController.h"

AMedusaCharacter::AMedusaCharacter()
{
	/**/
	/*IA Setting
	/**/
	//IA Controller Reference
	AIController = Cast<AMeduseAIController>(GetController());
	if (!AIController)
	{
		GLog->Log("Ai Controller non creato");
	}
	else
	{
		GLog->Log("AI");
	}
}

void AMedusaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AMedusaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	bIsGettingDameged = true;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMedusaCharacter::Die()
{

}

void AMedusaCharacter::DeadEnd()
{

}

void AMedusaCharacter::Disappear()
{

}
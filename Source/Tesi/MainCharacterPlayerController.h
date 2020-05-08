// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESI_API AMainCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	/**/
	/*Character HUD
	/**/
	//Reference to the HUD Assets in the editor For Main HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;
	//Variable to hold the widget after creating it For Main HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

	/**/
	/*Enemy HealthBar variables
	/**/
	//Variable to hold the widget after creating it For Enemy HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* EnemyHealthBar;
	//Bool that display Enemy HealthBar (Visible on Combatoverlap, hidden in Combatoverlapend)
	bool bEnemyHealthBarVisible;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	/**/
	/*Enemy HealthBar functions
	/**/
	//Display
	void DisplayEnemyHealthBar();
	//Hide
	void RemoveEnemyHealthBar();
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainCharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//MainPlayer HUD
	if (HUDOverlayAsset)
	{
		//Create the Widget
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		//
		EnemyHealthBar = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}
	//Add to the Viewport
	HUDOverlay->AddToViewport();
	//Set Visibility
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);

}

void AMainCharacterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Show Enemy HealthBar
void AMainCharacterPlayerController::DisplayEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = true;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("DisplayEnemyHealthBar"));
		EnemyHealthBar->RenderOpacity = 1.f;
	}
}

//
void AMainCharacterPlayerController::RemoveEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = false;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("RemoveEnemyHealthBar"));
		EnemyHealthBar->RenderOpacity = 0.f;
	}
}


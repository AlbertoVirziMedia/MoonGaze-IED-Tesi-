// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "MainCharacterPlayerController.h"
#include "MainTargetSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentOnTargetLockedOnOff, AActor*, TargetActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESI_API UMainTargetSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainTargetSystemComponent();

	/**/
	/*Only Variables
	/**/
	/**/
	/*Lock-On Variables
	/**/
	//The Minimum distance to enable target Lock-on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float MinimumDistanceToEnable;
	//The Closest Target distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float ClosestTargetDistance ;
	// The amount of time to break line of sight when actor gets behind an Object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float BreakLineOfSightDelay;
	//bool that check if the line between the player and the enemy is blocked
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System")
	bool bIsBreakingLineOfSight;
	// Lower this value is, easier it will be to switch new target on right or left.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float StartRotatingThreshold;
	// Set it to true if you want the character to rotate around the locked on target to enable you to setup strafe animations.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	bool ShouldControlRotationWhenLockedOn;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System")
	bool bIsSwitchingTarget;
	// The AActor Subclass to search for targetable Actors.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	TSubclassOf<AActor> TargetableActors;
	//Timer for Break of the line sight
	FTimerHandle LineOfSightBreakTimerHandle;
	//Timer for switching target
	FTimerHandle SwitchingTargetTimerHandle;


	//
	AActor* MainCharacter;
	//
	APlayerController* PlayerController;

	//Bool that check if the player is in lock
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Target System")
	bool TargetLocked;
	//Reference to the Nearest Target
	AActor* NearestTarget;

	/**/
	/*Widget Variables
	/**/
	// The Widget Class to use when locked on Target. If not defined, will fallback to a Text-rendered widget with a single O character.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	TSubclassOf<UUserWidget> TargetLockedOnWidgetClass;
	// The Widget Draw Size for the Widget class to use when locked on Target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float TargetLockedOnWidgetDrawSize;
	// OnTargetLockedOn and OnTargetLockedOff events can be used for this.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	bool ShouldDrawTargetLockedOnWidget;
	// The Relative Location to apply on Target LockedOn Widget when attached to a target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	FVector TargetLockedOnWidgetRelativeLocation;
	// Called when a target is locked off, either if it is out of reach (based on MinimumDistanceToEnable) or behind an Object.
	UPROPERTY(BlueprintAssignable, Category = "Target System")
	FComponentOnTargetLockedOnOff OnTargetLockedOff;
	// Called when a target is locked on
	UPROPERTY(BlueprintAssignable, Category = "Target System")
	FComponentOnTargetLockedOnOff OnTargetLockedOn;
	//UWidgetComponent* TargetLockedOnWidgetComponent;
	UWidgetComponent* TargetLockedOnWidgetComponent;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**/
	/*Only Functions
	/**/
	/**/
	/*Lock-On Functions
	/**/
	// Function to call to target a new actor.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void TargetActor();
	// Function to call to manually untarget.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void TargetLockOff();
	// Function to call to target a new actor.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void TargetActorWithAxisInput(float AxisValue);

	//Function that check if a character is targetable
	bool TargetIsTargetable(AActor* Actor);
	//
	void SetControlRotationOnTarget(AActor* TargetActor);
	//
	float GetDistanceFromCharacter(AActor* OtherActor);
	//
	bool ShouldBreakLineOfSight();
	//
	void BreakLineOfSight();
	//
	bool LineTrace(FHitResult& HitResult, AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>());
	//
	void ControlRotation(bool ShouldControlRotation);
	//
	TArray<AActor*> GetAllActorsOfClass(TSubclassOf<AActor> ActorClass);
	//
	FRotator GetControlRotationOnTarget(AActor* OtherActor);
	//
	void TargetLockOn(AActor* TargetToLockOn);
	//
	void CreateAndAttachTargetLockedOnWidgetComponent(AActor* TargetActor);
	//
	AActor* FindNearestTarget(TArray<AActor*> Actors);
	//
	bool LineTraceForActor(AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>());
	//
	bool IsInViewport(AActor* TargetActor);
	//
	TArray<AActor*> FindTargetsInRange(TArray<AActor*> ActorsToLook, float RangeMin, float RangeMax);
	//
	float GetAngleUsingCameraRotation(AActor* ActorToLook);
	//
	FRotator FindLookAtRotation(const FVector Start, const FVector Target);
	//
	void ResetIsSwitchingTarget();


private:



};

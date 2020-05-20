// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTargetSystemComponent.h"
#include "MainCharacterPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CollisionQueryParams.h"
#include "TargetSystemTargetableInterface.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Math/RotationMatrix.h"
#include "TargetSystemLockOnWidget.h"

// Sets default values for this component's properties
UMainTargetSystemComponent::UMainTargetSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/**/
	/*Only Variables
	/**/
	/**/
	/*Lock-on Variables
	/**/
	MinimumDistanceToEnable = 1200.f;
	ClosestTargetDistance = 0.f;
	BreakLineOfSightDelay = 2.f;
	bIsBreakingLineOfSight = false;
	StartRotatingThreshold = 1.5f;
	ShouldControlRotationWhenLockedOn = true;
	bIsSwitchingTarget = false;

	TargetableActors = APawn::StaticClass();

	/**/
	/*Target System Camera Variables
	/**/
	StartingCameraRotation = FRotator(0.f, 0.f, 0.f);
	ChangeZCameraPosition = 300;
	ChangeRollCameraRotation = 350;

	/**/
	/*Widgets Variables
	/**/
	TargetLockedOnWidgetDrawSize = 32.0f;
	TargetLockedOnWidgetRelativeLocation = FVector(0.0f, 0.0f, 20.0f);
	ShouldDrawTargetLockedOnWidget = true;

}


// Called when the game starts
void UMainTargetSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = GetOwner();
	if (!MainCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Cannot get Owner reference ..."), *this->GetName());
		return;
	}
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Cannot get PlayerController reference ..."), *MainCharacter->GetName());
		return;
	}
	
	UCameraComponent* CameraComponent = MainCharacter->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent)
	{

	}
	if (CameraComponent)
	{
		StartingCameraPosition = CameraComponent->GetRelativeLocation();
	}
}


// Called every frame
void UMainTargetSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetLocked && NearestTarget)
	{
		if (!TargetIsTargetable(NearestTarget))
		{
			TargetLockOff();
			return;
		}

		//
		SetControlRotationOnTarget(NearestTarget);

		// Target Locked Off based on Distance
		if (GetDistanceFromCharacter(NearestTarget) > MinimumDistanceToEnable)
		{
			TargetLockOff();
		}

		//
		if (ShouldBreakLineOfSight() && !bIsBreakingLineOfSight)
		{
			if (BreakLineOfSightDelay <= 0)
			{
				TargetLockOff();
			}
			else
			{
				bIsBreakingLineOfSight = true;
				GetWorld()->GetTimerManager().SetTimer(LineOfSightBreakTimerHandle, this, &UMainTargetSystemComponent::BreakLineOfSight, BreakLineOfSightDelay);
			}
		}
	}

	if (TargetLocked)
	{
		UCameraComponent* CameraComponent = MainCharacter->FindComponentByClass<UCameraComponent>();
		if (!CameraComponent)
		{
			
		}
		if (CameraComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
			CameraComponent->SetRelativeLocation(FMath::VInterpTo(FVector(StartingCameraPosition), FVector(StartingCameraPosition.X, StartingCameraPosition.Y, ChangeZCameraPosition), 5.f, 0.1f));
			CameraComponent->SetRelativeRotation(FMath::RInterpTo(FRotator(StartingCameraRotation), FRotator(ChangeRollCameraRotation, StartingCameraRotation.Pitch, StartingCameraRotation.Yaw), 5.f, 0.5f));
		}
	}

	if (!TargetLocked)
	{
		UCameraComponent* CameraComponent = MainCharacter->FindComponentByClass<UCameraComponent>();
		if (!CameraComponent)
		{

		}
		if (CameraComponent)
		{
			CameraComponent->SetRelativeLocation(FMath::VInterpTo(FVector(OnTargetCameraPosition), FVector(StartingCameraPosition), 5.f, 0.1f));
			CameraComponent->SetRelativeRotation(FMath::RInterpTo(FRotator(OnTargetCameraRotation), FRotator(StartingCameraRotation), 5.f, 0.1f));
		}
	}
}

bool UMainTargetSystemComponent::TargetIsTargetable(AActor* Actor)
{
	bool bIsImplemented = Actor->GetClass()->ImplementsInterface(UTargetSystemTargetableInterface::StaticClass());

	if (bIsImplemented)
	{
		return ITargetSystemTargetableInterface::Execute_IsTargetable(Actor);
	}

	return true;
}

//
void  UMainTargetSystemComponent::SetControlRotationOnTarget(AActor* TargetActor)
{
	if (!PlayerController)
	{
		return;
	}

	PlayerController->SetControlRotation(GetControlRotationOnTarget(TargetActor));
}

//
FRotator UMainTargetSystemComponent::GetControlRotationOnTarget(AActor* OtherActor)
{
	FRotator ControlRotation = PlayerController->GetControlRotation();

	FVector CharacterLocation = MainCharacter->GetActorLocation();
	FVector OtherActorLocation = OtherActor->GetActorLocation();

	// Find look at rotation
	FRotator LookRotation = FRotationMatrix::MakeFromX(OtherActorLocation - CharacterLocation).Rotator();

	FRotator TargetRotation = FRotator(LookRotation.Pitch, LookRotation.Yaw, ControlRotation.Roll);

	return FMath::RInterpTo(ControlRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
}

float UMainTargetSystemComponent::GetDistanceFromCharacter(AActor* OtherActor)
{
	return MainCharacter->GetDistanceTo(OtherActor);
}

bool UMainTargetSystemComponent::ShouldBreakLineOfSight()
{
	if (!NearestTarget)
	{
		return true;
	}

	TArray<AActor*> ActorsToIgnore = GetAllActorsOfClass(TargetableActors);
	ActorsToIgnore.Remove(NearestTarget);

	FHitResult HitResult;
	bool bHit = LineTrace(HitResult, NearestTarget, ActorsToIgnore);
	if (bHit && HitResult.GetActor() != NearestTarget)
	{
		return true;
	}

	return false;
}

//
void UMainTargetSystemComponent::BreakLineOfSight()
{
	bIsBreakingLineOfSight = false;
	if (ShouldBreakLineOfSight())
	{
		TargetLockOff();
	}
}

//
bool UMainTargetSystemComponent::LineTrace(FHitResult & HitResult, AActor* OtherActor, TArray<AActor*> ActorsToIgnore)
{

	FCollisionQueryParams Params = FCollisionQueryParams(FName("LineTraceSingle"));

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Init(MainCharacter, 1);
	IgnoredActors += ActorsToIgnore;

	Params.AddIgnoredActors(IgnoredActors);

	return GetWorld()->LineTraceSingleByChannel(HitResult, MainCharacter->GetActorLocation(), OtherActor->GetActorLocation(), ECollisionChannel::ECC_Pawn, Params);
}

//
void UMainTargetSystemComponent::TargetActor()
{
	ClosestTargetDistance = MinimumDistanceToEnable;

	if (TargetLocked)
	{
		TargetLockOff();
	}
	else
	{
		TArray<AActor*> Actors = GetAllActorsOfClass(TargetableActors);
		NearestTarget = FindNearestTarget(Actors);
		TargetLockOn(NearestTarget);
	}
}

//
AActor* UMainTargetSystemComponent::FindNearestTarget(TArray<AActor*> Actors)
{
	TArray<AActor*> ActorsHit;

	// Find all actors we can line trace to
	for (AActor* Actor : Actors)
	{
		bool bHit = LineTraceForActor(Actor);
		if (bHit && IsInViewport(Actor))
		{
			ActorsHit.Add(Actor);
		}
	}

	// From the hit actors, check distance and return the nearest
	if (ActorsHit.Num() == 0)
	{
		return nullptr;
	}

	float ClosestDistance = ClosestTargetDistance;
	AActor* Target = nullptr;
	for (AActor* Actor : ActorsHit)
	{
		float Distance = GetDistanceFromCharacter(Actor);
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			Target = Actor;
		}
	}

	return Target;
}

//
bool UMainTargetSystemComponent::LineTraceForActor(AActor* OtherActor, TArray<AActor*> ActorsToIgnore)
{
	FHitResult HitResult;
	bool bHit = LineTrace(HitResult, OtherActor, ActorsToIgnore);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == OtherActor)
		{
			return true;
		}
	}

	return false;
}

//
bool UMainTargetSystemComponent::IsInViewport(AActor* TargetActor)
{
	if (!PlayerController)
	{
		return true;
	}

	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(TargetActor->GetActorLocation(), ScreenLocation);

	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);

	return ScreenLocation.X > 0 && ScreenLocation.Y > 0 && ScreenLocation.X < ViewportSize.X && ScreenLocation.Y < ViewportSize.Y;
}

//
void UMainTargetSystemComponent::TargetLockOn(AActor* TargetToLockOn)
{
	if (TargetToLockOn)
	{
		TargetLocked = true;
		if (ShouldDrawTargetLockedOnWidget)
		{
			CreateAndAttachTargetLockedOnWidgetComponent(TargetToLockOn);
		}

		if (ShouldControlRotationWhenLockedOn)
		{
			ControlRotation(true);
		}

		PlayerController->SetIgnoreLookInput(true);

		if (OnTargetLockedOn.IsBound())
		{
			OnTargetLockedOn.Broadcast(TargetToLockOn);
		}

	}
}

void UMainTargetSystemComponent::CreateAndAttachTargetLockedOnWidgetComponent(AActor* TargetActor)
{
	TargetLockedOnWidgetComponent = NewObject<UWidgetComponent>(TargetActor, FName("TargetLockOn"));
	if (TargetLockedOnWidgetClass)
	{
		TargetLockedOnWidgetComponent->SetWidgetClass(TargetLockedOnWidgetClass);
	}
	else
	{
		TargetLockedOnWidgetComponent->SetWidgetClass(UTargetSystemLockOnWidget::StaticClass());
	}

	TargetLockedOnWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TargetLockedOnWidgetComponent->SetupAttachment(TargetActor->GetRootComponent());
	TargetLockedOnWidgetComponent->SetRelativeLocation(TargetLockedOnWidgetRelativeLocation);
	TargetLockedOnWidgetComponent->SetDrawSize(FVector2D(TargetLockedOnWidgetDrawSize, TargetLockedOnWidgetDrawSize));
	TargetLockedOnWidgetComponent->SetVisibility(true);
	TargetLockedOnWidgetComponent->RegisterComponent();
}

void UMainTargetSystemComponent::TargetLockOff()
{
	TargetLocked = false;

	if (NearestTarget)
	{
		if (ShouldControlRotationWhenLockedOn)
		{
			ControlRotation(false);
		}

		PlayerController->ResetIgnoreLookInput();

/*		if (OnTargetLockedOff.IsBound())
		{
			OnTargetLockedOff.Broadcast(NearestTarget);
		}
*/
	}

	UCameraComponent* CameraComponent = MainCharacter->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent)
	{

	}
	if (CameraComponent)
	{
		OnTargetCameraPosition = CameraComponent->GetRelativeLocation();
		OnTargetCameraRotation = CameraComponent->GetRelativeRotation();
	}

	NearestTarget = nullptr;
}

//
void UMainTargetSystemComponent::ControlRotation(bool ShouldControlRotation)
{
	APawn* Pawn = Cast<APawn>(MainCharacter);
	if (Pawn)
	{
		Pawn->bUseControllerRotationYaw = ShouldControlRotation;
	}

	UCharacterMovementComponent* CharacterMovementComponent = MainCharacter->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->bOrientRotationToMovement = !ShouldControlRotation;
	}
}

//
TArray<AActor*> UMainTargetSystemComponent::GetAllActorsOfClass(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> Actors;
	for (TActorIterator<AActor> ActorIterator(GetWorld(), ActorClass); ActorIterator; ++ActorIterator)
	{
		AActor* Actor = *ActorIterator;
		bool IsTargetable = TargetIsTargetable(Actor);
		if (IsTargetable)
		{
			Actors.Add(Actor);
		}
	}

	return Actors;
}

void UMainTargetSystemComponent::TargetActorWithAxisInput(float AxisValue)
{
	// If Axis value does not exceeds configured threshold, do nothing
	if (FMath::Abs(AxisValue) < StartRotatingThreshold)
	{
		return;
	}

	// If we're not locked on, do nothing
	if (!TargetLocked)
	{
		return;
	}

	// If we're switching target, do nothing for a set amount of time
	if (bIsSwitchingTarget)
	{
		return;
	}

	// Lock off target
	AActor* CurrentTarget = NearestTarget;

	// Depending on Axis Value negative / positive, set Direction to Look for (negative: left, positive: right)
	float RangeMin = AxisValue < 0 ? 0 : 180;
	float RangeMax = AxisValue < 0 ? 180 : 360;

	// Reset Closest Target Distance to Minimum Distance to Enable
	ClosestTargetDistance = MinimumDistanceToEnable;

	// Get All Actors of Class
	TArray<AActor*> Actors = GetAllActorsOfClass(TargetableActors);

	// For each of these actors, check line trace and ignore Current Target and build the list of actors to look from
	TArray<AActor*> ActorsToLook;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(CurrentTarget);
	for (AActor* Actor : Actors)
	{
		bool bHit = LineTraceForActor(Actor, ActorsToIgnore);
		if (bHit && IsInViewport(Actor))
		{
			ActorsToLook.Add(Actor);
		}
	}

	// Find Targets in Range (left or right, based on Character and CurrentTarget)
	TArray<AActor*> TargetsInRange = FindTargetsInRange(ActorsToLook, RangeMin, RangeMax);

	// For each of these targets in range, get the closest one to current target
	AActor* ActorToTarget = nullptr;
	for (AActor* Actor : TargetsInRange)
	{
		// and filter out any character too distant from minimum distance to enable
		float Distance = GetDistanceFromCharacter(Actor);
		if (Distance < MinimumDistanceToEnable)
		{
			float RelativeActorsDistance = CurrentTarget->GetDistanceTo(Actor);
			if (RelativeActorsDistance < ClosestTargetDistance)
			{
				ClosestTargetDistance = RelativeActorsDistance;
				ActorToTarget = Actor;
			}
		}
	}

	if (ActorToTarget)
	{
		bIsSwitchingTarget = true;
		TargetLockOff();
		NearestTarget = ActorToTarget;
		TargetLockOn(ActorToTarget);
		GetWorld()->GetTimerManager().SetTimer(SwitchingTargetTimerHandle, this, &UMainTargetSystemComponent::ResetIsSwitchingTarget, 0.5f);
	}
}

//
TArray<AActor*> UMainTargetSystemComponent::FindTargetsInRange(TArray<AActor*> ActorsToLook, float RangeMin, float RangeMax)
{
	TArray<AActor*> ActorsInRange;

	for (AActor* Actor : ActorsToLook)
	{
		float Angle = GetAngleUsingCameraRotation(Actor);
		if (Angle > RangeMin && Angle < RangeMax)
		{
			ActorsInRange.Add(Actor);
		}
	}

	return ActorsInRange;
}

//
float UMainTargetSystemComponent::GetAngleUsingCameraRotation(AActor* ActorToLook)
{
	UCameraComponent* CameraComponent = MainCharacter->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetSystem::GetAngleUsingCameraRotation() Cannot get reference to camera component"));
		return 0.0f;
	}

	FRotator CameraWorldRotation = CameraComponent->GetComponentRotation();
	FRotator LookAtRotation = FindLookAtRotation(CameraComponent->GetComponentLocation(), ActorToLook->GetActorLocation());

	float YawAngle = CameraWorldRotation.Yaw - LookAtRotation.Yaw;
	if (YawAngle < 0)
	{
		YawAngle = YawAngle + 360;
	}

	return YawAngle;
}

//
FRotator UMainTargetSystemComponent::FindLookAtRotation(const FVector Start, const FVector Target)
{
	return FRotationMatrix::MakeFromX(Target - Start).Rotator();
}

//
void UMainTargetSystemComponent::ResetIsSwitchingTarget()
{
	bIsSwitchingTarget = false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnComponent.h"

// Sets default values for this component's properties
UPawnComponent::UPawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UPawnComponent::BeginPlay()
{
	Super::BeginPlay();

	GetPhysicsHandleComponent();
	BindInputActions();
}

// Called every frame
void UPawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * 100.f;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	else
	{
	}

}


void UPawnComponent::GetPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle is missing"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle found"))
	}
}
void UPawnComponent::BindInputActions()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent is missing"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found"))

			InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UPawnComponent::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UPawnComponent::Release);
	}
}

FHitResult UPawnComponent::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * 100.f;


	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_PhysicsBody);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		OQP,
		TraceParams
	);

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT: %s "),
			*Hit.GetActor()->GetName())
	}

	return Hit;
}

void UPawnComponent::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"))

	auto ActorToGrab = GetFirstPhysicsBodyInReach();

	
		PhysicsHandle->GrabComponent(
			ActorToGrab.GetComponent(),
			NAME_None,
			ActorToGrab.GetActor()->GetActorLocation(),
			false
		);
	
}
void UPawnComponent::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release"));

	PhysicsHandle->ReleaseComponent();
}

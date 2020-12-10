// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnComponent.h"

UPawnComponent::UPawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UPawnComponent::BeginPlay()
{
	Super::BeginPlay();

	GetPhysicsHandleComponent();
	BindInputActions();
}

void UPawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachStart());
	}
}

void UPawnComponent::GetPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

FHitResult UPawnComponent::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_PhysicsBody);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetReachStart(),
		GetReachEnd(),
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

FVector UPawnComponent::GetReachStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}
FVector UPawnComponent::GetReachEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * 100.f;
}

void UPawnComponent::Grab()
{
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
	PhysicsHandle->ReleaseComponent();
}

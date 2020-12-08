// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	OpenDoor();
}

void UDoorOpen::OpenDoor()
{
	
	if (PressurePlate->IsOverlappingActor(actorThatOpens))
	{
		GetOwner()->SetActorRotation(FRotator(0.f, -65.f, 0.f));
	}
	else
	{
		GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
}

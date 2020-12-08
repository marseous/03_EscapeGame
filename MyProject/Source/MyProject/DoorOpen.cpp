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
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	thisDoor = GetOwner();

}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(player))
	{
		OpenDoor();
	}

	if (GetWorld()->GetTimeSeconds() - lastTimeOpen > closeDoorDelay)
	{
		CloseDoor();
	}
}

void UDoorOpen::OpenDoor()
{
	thisDoor->SetActorRotation(FRotator(0.f, -65.f, 0.f));
	lastTimeOpen = GetWorld()->GetTimeSeconds();
}

void UDoorOpen::CloseDoor()
{
	thisDoor->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

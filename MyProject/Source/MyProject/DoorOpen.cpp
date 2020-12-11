// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPlate() > 20.f)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

}

float UDoorOpen::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;

	TSet<AActor*> OverlappingActors;
	if (PressurePlate != nullptr)
	{
		PressurePlate->GetOverlappingActors(OverlappingActors);
	}

	for (auto& actor : OverlappingActors)
	{
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}


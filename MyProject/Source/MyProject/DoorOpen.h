// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorOpen();

protected:
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOnPlate();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable) FOnOpenRequest OpenRequest;

	UPROPERTY(VisibleAnywhere)	float DoorAngle = -90.f;
	UPROPERTY(EditAnywhere)		float closeDoorDelay = 1.f;
								float lastTimeOpen;

	UPROPERTY(EditAnywhere)		ATriggerVolume* PressurePlate = nullptr;
								AActor* thisDoor = nullptr;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpen.h"
#include "GameFramework/Actor.h"

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

	InitialYaw = GetOwner() -> GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	if (PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no PressurePlate set"), *GetOwner() -> GetName())
	}
	
	ActorThatOpens = GetWorld() -> GetFirstPlayerController() -> GetPawn();
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate -> IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld() -> GetTimeSeconds();
	}
	else
	{
		if (GetWorld() -> GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}	
	}

	
}

void UDoorOpen::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner() -> GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
}

void UDoorOpen::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner() -> GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
}

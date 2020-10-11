// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber_2.h"

#define OUT

// Sets default values for this component's properties
UGrabber_2::UGrabber_2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber_2::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber_2::SetupInputComponent()
{
	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber_2::Grab);
		InputComponent -> BindAction("Grab", IE_Released, this, &UGrabber_2::Release);
	}
}

void UGrabber_2::FindPhysicsHandle()
{
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle found.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *GetOwner() -> GetName());
	}
}

void UGrabber_2::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));

	// TODO only raycast when key is pressed and see if we reach any actors with physics body collide channel set.

	// If we hit something then attach a physics handle.
	// TODO attach physics handle.
}

void UGrabber_2::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
	// TODO remove/release the physics handle.
}

// Called every frame
void UGrabber_2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If physics handle is attached
		// Move the object we are holding.

	GetFirstPhysicsBodyInReach();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get the players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Ray.cast out to a certain distance (Reach)
	GetWorld() -> LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	// this should be removed - test
	// See what it hits
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit -> GetName()))
	}
	// Logging out to test
}


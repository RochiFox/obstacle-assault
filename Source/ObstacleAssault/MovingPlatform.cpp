// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get current location
	FVector CurrentLocation = GetActorLocation();

	// Add vector to that location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;

	// Set the location
	SetActorLocation(CurrentLocation);

	// Check the distance
	float PlatformDistance = FVector::Dist(StartLocation, CurrentLocation);

	// Reverse the direction when platform gone too far
	if (PlatformDistance > MoveDistance)
	{
		// Find a distance
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);

		// Return platform back
		PlatformVelocity = -PlatformVelocity;
	}
}

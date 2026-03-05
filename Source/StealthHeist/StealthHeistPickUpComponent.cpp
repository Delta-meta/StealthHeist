// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthHeistPickUpComponent.h"

UStealthHeistPickUpComponent::UStealthHeistPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UStealthHeistPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UStealthHeistPickUpComponent::OnSphereBeginOverlap);
}

void UStealthHeistPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AStealthHeistCharacter* Character = Cast<AStealthHeistCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}

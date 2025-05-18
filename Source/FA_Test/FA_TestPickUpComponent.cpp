// Copyright Epic Games, Inc. All Rights Reserved.

#include "FA_TestPickUpComponent.h"

UFA_TestPickUpComponent::UFA_TestPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UFA_TestPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UFA_TestPickUpComponent::OnSphereBeginOverlap);
}

void UFA_TestPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AFA_TestCharacter* Character = Cast<AFA_TestCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}

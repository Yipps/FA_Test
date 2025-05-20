// Fill out your copyright notice in the Description page of Project Settings.


#include "FA_InteractorComponent.h"

#include "FA_IInteractable.h"
#include "KismetTraceUtils.h"

// Sets default values for this component's properties
UFA_InteractorComponent::UFA_InteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFA_InteractorComponent::TraceInteract()
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (AController* Controller = Pawn->GetController())
		{
			FVector StartLocation;
			FRotator StartRotation;
			
			Controller->GetPlayerViewPoint(StartLocation, StartRotation);
			FVector EndLocation = StartLocation + StartRotation.Vector() * TraceLength;

			FCollisionQueryParams TraceParams;
			TraceParams.AddIgnoredActor(Pawn);

			FHitResult HitResult;
			if (bool DidHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams))
			{
				if (AActor* HitActor = HitResult.GetActor())
				{
					if (IFA_IInteractable* Interactable = Cast<IFA_IInteractable>(HitActor))
					{
						IFA_IInteractable::Execute_Interact(HitActor, Pawn);
					}
				}
				DrawDebugLineTraceSingle(GetWorld(),StartLocation,EndLocation,EDrawDebugTrace::ForDuration, DidHit, HitResult, FColor::Red, FColor::Green, 2.f);
			}
		}
	}
}


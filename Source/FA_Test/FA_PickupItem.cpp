// Fill out your copyright notice in the Description page of Project Settings.


#include "FA_PickupItem.h"

#include "FAInventoryComponent.h"

// Sets default values for this component's properties
AFA_PickupItem::AFA_PickupItem()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = CollisionSphere;

	Mesh->SetupAttachment(RootComponent);
}

bool AFA_PickupItem::Interact_Implementation(AActor* InstigatorActor)
{
	IFA_IInteractable::Interact_Implementation(InstigatorActor);
	if (UFAInventoryComponent* Inventory = UFAInventoryComponent::GetInventoryComponent(InstigatorActor))
	{
		if (Inventory->CanAddItem())
		{
			Inventory->AddItem(Item);
			Destroy();
			return true;
		}
	}
	return false;
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FA_IInteractable.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "FA_PickupItem.generated.h"


class UInventoryDataAsset;

UCLASS()
class FA_TEST_API AFA_PickupItem : public AActor, public IFA_IInteractable
{
private:
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AFA_PickupItem();
	virtual bool Interact_Implementation(AActor* InstigatorActor) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	UInventoryDataAsset* Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	UMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	USphereComponent* CollisionSphere;

	
		
};

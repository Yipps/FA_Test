// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FAInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInventoryChangeDelegate, UInventoryDataAsset*, item, int, index, bool, bNewItemAdded);

class UInventoryDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FA_TEST_API UFAInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	static UFAInventoryComponent* GetInventoryComponent(AActor* Actor);
	
	// Sets default values for this component's properties
	UFAInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UInventoryDataAsset* ItemToAdd);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UInventoryDataAsset* ItemToRemove);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SwapItems(UInventoryDataAsset* Item, int NewPosition);


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanAddItem();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UInventoryDataAsset* Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int FindItemIndex(UInventoryDataAsset* Item);
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryChangeDelegate OnInventoryChange;

	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int MaxItems = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<UInventoryDataAsset*> Items;


#if WITH_EDITOR
	// Called whenever a property is edited in the editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);

		// Enforce size of the inventory
		if (Items.Num() != MaxItems)
		{
			Items.SetNum(MaxItems); // Trim the array if it exceeds the max size
		}
	}
#endif


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

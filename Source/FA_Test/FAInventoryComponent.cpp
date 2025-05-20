// Fill out your copyright notice in the Description page of Project Settings.


#include "FAInventoryComponent.h"

// Sets default values for this component's properties
UFAInventoryComponent::UFAInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Items.SetNum(MaxItems);
}

void UFAInventoryComponent::AddItem(UInventoryDataAsset* ItemToAdd)
{
	if (!CanAddItem())
		return;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == nullptr)
		{
			Items[i] = ItemToAdd;
			OnInventoryChange.Broadcast(ItemToAdd, i, true);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Attempted to add to inventory when it was full"));
}

void UFAInventoryComponent::RemoveItem(UInventoryDataAsset* ItemToRemove)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == ItemToRemove)
		{
			Items[i] = nullptr;
			OnInventoryChange.Broadcast(ItemToRemove, i, false);
			return;
		}
	}
}

bool UFAInventoryComponent::SwapItems(UInventoryDataAsset* Item, int NewPosition)
{
	if (NewPosition < 0 || NewPosition >= Items.Num())
		return false;

	int OldIndex = FindItemIndex(Item);
	
	UInventoryDataAsset* TempItem = Items[NewPosition];

	Items[OldIndex] = TempItem;
	Items[NewPosition] = Item;

	OnInventoryChange.Broadcast(Item, NewPosition, false);
	OnInventoryChange.Broadcast(TempItem, OldIndex, false);
	return true;


}

bool UFAInventoryComponent::CanAddItem()
{
	return Items.Num() < MaxItems;
}

int UFAInventoryComponent::FindItemIndex(UInventoryDataAsset* Item)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == Item)
			return i;
	}
	return -1;
}

bool UFAInventoryComponent::HasItem(UInventoryDataAsset* Item)
{
	return FindItemIndex(Item) != -1;
}


// Called when the game starts
void UFAInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFAInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


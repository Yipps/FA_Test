// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FA_TEST_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	
};

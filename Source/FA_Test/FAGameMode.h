// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FA_TestGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "FAGameMode.generated.h"

class AFAPhotoRoom;
/**
 * 
 */
UCLASS()
class FA_TEST_API AFAGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFAGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "PhotoRoom")
	TSubclassOf<AFAPhotoRoom> PhotoRoomClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	FVector PhotoRoomLocation;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "PhotoRoom")
	AFAPhotoRoom* PhotoRoomInstance;
	
	
};

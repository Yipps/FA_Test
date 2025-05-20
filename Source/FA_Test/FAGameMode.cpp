// Fill out your copyright notice in the Description page of Project Settings.


#include "FAGameMode.h"

#include "FAPhotoRoom.h"

AFAGameMode::AFAGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AFAGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	PhotoRoomInstance = GetWorld()->SpawnActor<AFAPhotoRoom>(PhotoRoomClass, PhotoRoomLocation, FRotator::ZeroRotator);

	if (!PhotoRoomInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn PhotoRoom"));
	}
}

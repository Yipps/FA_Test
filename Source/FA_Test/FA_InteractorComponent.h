// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FA_InteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FA_TEST_API UFA_InteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFA_InteractorComponent();

	UFUNCTION(BlueprintCallable)
	void TraceInteract();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float TraceLength = 5000;






};

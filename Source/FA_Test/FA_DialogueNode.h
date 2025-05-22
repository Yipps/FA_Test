// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FA_DialogueNode.generated.h"

struct FStructLine;
struct FChoice;

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ReponseText;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	UFA_DialogueNode* Node;
};


UCLASS(Blueprintable,CollapseCategories,EditInlineNew)
class FA_TEST_API UFA_DialogueNode : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(FullyExpand=true), BlueprintReadOnly)
	FText NPC_Line;
	UPROPERTY(EditAnywhere, meta=(FullyExpand=true), BlueprintReadOnly)	
	TArray<FChoice> Choices;

	UFUNCTION(BlueprintCallable)
	bool NeedsChoice();
	
protected:

	UFUNCTION(BlueprintCallable)
	FText GetLine();
	UFUNCTION(BlueprintCallable)
	UFA_DialogueNode* GetNextNode(int Choice);

	
	
};


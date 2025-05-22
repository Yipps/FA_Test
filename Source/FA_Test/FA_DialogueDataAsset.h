
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FA_DialogueDataAsset.generated.h"

class UFA_DialogueNode;

// USTRUCT()
// struct FStructResponse : public FTableRowBase
// {
// 	GENERATED_BODY()
// 	
// 	UPROPERTY(EditAnywhere)
// 	FText Response;
//
// 	UPROPERTY(EditAnywhere)
// 	UFA_DialogueDataAsset* NextDialogue;
// 	
// };
//
// USTRUCT()
// struct FStructLine : public FTableRowBase
// {
// 	GENERATED_BODY()
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	TArray<FText> NPC_Text;
//
// 	UPROPERTY(EditAnywhere,meta = (ShowOnlyInnerProperties), BlueprintReadOnly)
// 	TArray<FStructResponse> Responses;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	bool PlayNextLine = false;
// };


UCLASS(BlueprintType)
class FA_TEST_API UFA_DialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Speaker;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta=(FullyExpand=true))
	TArray<UFA_DialogueNode*> DialogueBranches;

	
	void ResetNodes();
};



// Fill out your copyright notice in the Description page of Project Settings.


#include "FA_DialogueNode.h"


bool UFA_DialogueNode::NeedsChoice()
{
	if (Choices.Num() > 0 && !Choices[0].ReponseText.IsEmptyOrWhitespace())
	{
		return true;
	}
	return false;
}

FText UFA_DialogueNode::GetLine()
{
	return NPC_Line;
}

UFA_DialogueNode* UFA_DialogueNode::GetNextNode(int Choice = 0)
{
	if (Choices.Num() <= 0 || Choice < 0 || Choice >= Choices.Num())
	{
		return nullptr;
	}
	return Choices[Choice].Node;
}

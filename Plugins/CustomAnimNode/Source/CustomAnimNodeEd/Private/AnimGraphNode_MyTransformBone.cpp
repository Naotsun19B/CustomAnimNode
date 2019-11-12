// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomAnimNodeEd.h"
#include "AnimGraphNode_MyTransformBone.h"

#define LOCTEXT_NAMESPACE "CustomAnimNodeEd"

UAnimGraphNode_MyTransformBone::UAnimGraphNode_MyTransformBone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText UAnimGraphNode_MyTransformBone::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("AnimGraphNode_MyTransformBone_Title", "My Transform Bone");
}

#undef LOCTEXT_NAMESPACE
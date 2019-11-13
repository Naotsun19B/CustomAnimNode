// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_MyTransformBone.h"
#include "CustomAnimNodeEd.h"

#define LOCTEXT_NAMESPACE "CustomAnimNodeEd"

UAnimGraphNode_MyTransformBone::UAnimGraphNode_MyTransformBone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText UAnimGraphNode_MyTransformBone::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("AnimGraphNode_MyTransformBone_Title", "My Transform Bone");
}

FLinearColor UAnimGraphNode_MyTransformBone::GetNodeTitleColor() const
{
	return FLinearColor(0.f, 1.f, 0.f);
}

FText UAnimGraphNode_MyTransformBone::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_MyTransformBone_Tooltip", "This is my first custom anim node.");
}

#undef LOCTEXT_NAMESPACE
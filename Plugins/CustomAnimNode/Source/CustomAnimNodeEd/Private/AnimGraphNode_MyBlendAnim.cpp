// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_MyBlendAnim.h"

#define LOCTEXT_NAMESPACE "MyBlendAnim"

UAnimGraphNode_MyBlendAnim::UAnimGraphNode_MyBlendAnim(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText UAnimGraphNode_MyBlendAnim::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("AnimGraphNode_MyBlendAnim_Title", "My Blend Anim");
}

FLinearColor UAnimGraphNode_MyBlendAnim::GetNodeTitleColor() const
{
	return FLinearColor(0.f, 1.f, 0.f);
}

FText UAnimGraphNode_MyBlendAnim::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_MyBlendAnim_Tooltip", "My Blend Anim");
}

void UAnimGraphNode_MyBlendAnim::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ReconstructNode();
}

#undef LOCTEXT_NAMESPACE
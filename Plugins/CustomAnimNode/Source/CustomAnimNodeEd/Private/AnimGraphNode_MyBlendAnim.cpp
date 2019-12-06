// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_MyBlendAnim.h"

#define LOCTEXT_NAMESPACE "MyBlendAnim"

UAnimGraphNode_MyBlendAnim::UAnimGraphNode_MyBlendAnim(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText UAnimGraphNode_MyBlendAnim::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if ((TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle) && (Node.BoneToModify.BoneName == NAME_None))
	{
		return LOCTEXT("MyBlendAnim", "My Blend Anim");
	}
	else
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ControllerDescription"), LOCTEXT("MyBlendAnim", "My Blend Anim"));
		Args.Add(TEXT("BoneName"), FText::FromName(Node.BoneToModify.BoneName));

		if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_MyBlendAnim_ListTitle", "{ControllerDescription} - Bone: {BoneName}"), Args), this);
		}
		else
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_MyBlendAnim_Title", "{ControllerDescription}\nBone: {BoneName}"), Args), this);
		}
	}
	return CachedNodeTitles[TitleType];
}

FLinearColor UAnimGraphNode_MyBlendAnim::GetNodeTitleColor() const
{
	return FLinearColor(0.f, 1.f, 0.f);
}

FText UAnimGraphNode_MyBlendAnim::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_MyBlendAnim_Tooltip",
		"Blends hand animation based on AnimState.\n"
		"All child bones of specified bone will be blended."
	);
}

void UAnimGraphNode_MyBlendAnim::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ReconstructNode();
}

#undef LOCTEXT_NAMESPACE
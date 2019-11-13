// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_MySkeletalControl.h"
#include "CustomAnimNodeEd.h"

#define LOCTEXT_NAMESPACE "MySkeletalControl"

UAnimGraphNode_MySkeletalControl::UAnimGraphNode_MySkeletalControl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText UAnimGraphNode_MySkeletalControl::GetControllerDescription() const
{
	return LOCTEXT("MySkeletalControl", "MySkeletalControl");
}

FText UAnimGraphNode_MySkeletalControl::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if ((TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle) && (Node.TargetBone.BoneName == NAME_None))
	{
		return GetControllerDescription();
	}
	else
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ControllerDescription"), GetControllerDescription());
		Args.Add(TEXT("BoneName"), FText::FromName(Node.TargetBone.BoneName));

		if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_ModifyBone_ListTitle", "{ControllerDescription} - Target Bone: {BoneName}"), Args), this);
		}
		else
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_ModifyBone_Title", "{ControllerDescription}\nTarget Bone: {BoneName}"), Args), this);
		}
	}
	return CachedNodeTitles[TitleType];
}

void UAnimGraphNode_MySkeletalControl::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ReconstructNode();
}

FEditorModeID UAnimGraphNode_MySkeletalControl::GetEditorMode() const
{
	return "AnimGraph.SkeletalControl.MySkeletalControl";
}

#undef LOCTEXT_NAMESPACE
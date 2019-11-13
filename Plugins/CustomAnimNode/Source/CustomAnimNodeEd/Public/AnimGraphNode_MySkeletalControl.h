// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_MySkeletalControl.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "AnimGraphNode_MySkeletalControl.generated.h"

UCLASS()
class CUSTOMANIMNODEED_API UAnimGraphNode_MySkeletalControl : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Settings")
		FAnimNode_MySkeletalControl Node;

public:
	UAnimGraphNode_MySkeletalControl(const FObjectInitializer& ObjectInitializer);

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface

protected:
	// UAnimGraphNode_Base interface
	virtual FEditorModeID GetEditorMode() const override;
	virtual FText GetControllerDescription() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }
	// End of UAnimGraphNode_Base interface

private:
	/** Constructing FText strings can be constly, so we cache the node's title **/
	FNodeTitleTextTable CachedNodeTitles;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_MyTransformBone.h"
#include "AnimGraphNode_MyTransformBone.generated.h"

UCLASS()
class CUSTOMANIMNODEED_API UAnimGraphNode_MyTransformBone : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Settings")
		FAnimNode_MyTransformBone Node;

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
};

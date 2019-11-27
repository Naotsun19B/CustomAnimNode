#pragma once

#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimationRuntime.h"
#include "AnimNode_MyBlendAnimInternal.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct CUSTOMANIMNODE_API FAnimNode_MyBlendAnimInternal : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_1;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_3;

	float IsState2 = 0.f;
	float IsState3 = 0.f;

private:
	FAnimNode_SequencePlayer AnimNode_1;
	FAnimNode_SequencePlayer AnimNode_2;
	FAnimNode_SequencePlayer AnimNode_3;

public:
	FAnimNode_MyBlendAnimInternal();

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
};

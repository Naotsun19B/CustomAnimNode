#pragma once

#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimationRuntime.h"
#include "AnimNode_LayeredBoneBlend.h"
#include "AnimNode_MyBlendAnim.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct CUSTOMANIMNODE_API FAnimNode_MyBlendAnimInternal : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Alpha")
		float AlphaBase;

	UPROPERTY(EditAnywhere, Category = "Alpha")
		float Alpha_1;

	UPROPERTY(EditAnywhere, Category = "Alpha")
		float Alpha_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_1;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_3;

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

USTRUCT(BlueprintInternalUseOnly)
struct CUSTOMANIMNODE_API FAnimNode_MyBlendAnim : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Links")
		FPoseLink SourcePose;

	UPROPERTY(EditAnywhere, Category = "Modify Target")
		FBoneReference BoneToModify;

	UPROPERTY(EditAnywhere, Category = "Alpha")
		float AlphaBase;

	UPROPERTY(EditAnywhere, Category = "Alpha")
		float Alpha_1;

	UPROPERTY(EditAnywhere, Category = "Alpha")
		float Alpha_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_1;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_3;

private:
	FAnimNode_MyBlendAnimInternal InternalNode;
	FAnimNode_LayeredBoneBlend LayeredBoneBlendNode;

public:
	FAnimNode_MyBlendAnim();

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
};
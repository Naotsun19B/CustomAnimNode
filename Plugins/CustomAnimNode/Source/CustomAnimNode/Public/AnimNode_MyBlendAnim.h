#pragma once

#include "Animation/AnimNodeBase.h"
#include "AnimNode_LayeredBoneBlend.h"
#include "AnimNode_MyBlendAnimInternal.h"
#include "AnimNode_MyBlendAnim.generated.h"

UENUM(BlueprintType)
enum class EAnimState : uint8
{
	AS_State1	UMETA(DisplayName = "State1"),
	AS_State2	UMETA(DisplayName = "State2"),
	AS_State3	UMETA(DisplayName = "State3"),
	AS_Unknown	UMETA(DisplayName = "Unknown")
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

	UPROPERTY(EditAnywhere, Category = "State", meta = (PinShownByDefault))
		EAnimState AnimState = EAnimState::AS_Unknown;

	UPROPERTY(EditAnywhere, Category = "State")
		float InterpSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_1;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_2;

	UPROPERTY(EditAnywhere, Category = "Animation Asset")
		UAnimSequence* Animation_3;

private:
	FAnimNode_MyBlendAnimInternal InternalNode;
	FAnimNode_LayeredBoneBlend LayeredBoneBlendNode;
	float BeforeFrameIsState2 = 0.f;
	float BeforeFrameIsState3 = 0.f;
	float BeforeFrameAlpha = 0.f;

public:
	FAnimNode_MyBlendAnim();

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;

private:
	void GetHandState(float DeltaTime, float& IsState2, float& IsState3, float& Alpha);
};
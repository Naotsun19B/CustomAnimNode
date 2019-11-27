#pragma once

#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeSpaceConversions.h"
#include "BoneControllers/AnimNode_ModifyBone.h"
#include "AnimNode_MyTransformBone.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct CUSTOMANIMNODE_API FAnimNode_MyTransformBone : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Links")
		FPoseLink SourcePose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinShownByDefault))
		FVector Translation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinShownByDefault))
		TEnumAsByte<EBoneModificationMode> TranslationMode;

private:
	FAnimNode_ConvertLocalToComponentSpace LocalToComponentNode;
	FAnimNode_ModifyBone ModifyBoneNode;
	FAnimNode_ConvertComponentToLocalSpace ComponentToLocalNode;

public:
	FAnimNode_MyTransformBone();

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
};
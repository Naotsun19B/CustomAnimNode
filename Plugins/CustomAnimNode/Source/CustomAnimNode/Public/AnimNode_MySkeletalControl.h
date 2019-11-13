#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "BoneControllers/AnimNode_LookAt.h"
#include "AnimNode_MySkeletalControl.generated.h"

USTRUCT(BlueprintType)
struct CUSTOMANIMNODE_API FAnimNode_MySkeletalControl : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Target")
		FBoneReference TargetBone;
	
	UPROPERTY(EditAnywhere, Category = "Location", meta = (PinShownByDefault))
		FVector LookAtLocation;

protected:
	FAnimNode_LookAt LookAtNode;

public:
	FAnimNode_MySkeletalControl();

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	// End of FAnimNode_Base interface

	// FAnimNode_SkeletalControlBase interface
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;
	// End of FAnimNode_SkeletalControlBase interface

private:
	// FAnimNode_SkeletalControlBase interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface
};
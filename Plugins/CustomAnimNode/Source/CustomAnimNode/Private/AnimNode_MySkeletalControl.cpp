#include "AnimNode_MySkeletalControl.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"

FAnimNode_MySkeletalControl::FAnimNode_MySkeletalControl()
	: LookAtLocation(FVector::ZeroVector)
	, LookAtNode()
{

}

void FAnimNode_MySkeletalControl::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_SkeletalControlBase::Initialize_AnyThread(Context);
	FBoneContainer& RequiredBones = Context.AnimInstanceProxy->GetRequiredBones();
	InitializeBoneReferences(RequiredBones);
	LookAtNode.Initialize_AnyThread(Context);
	LookAtNode.BoneToModify = TargetBone;
	LookAtNode.LookAtLocation = LookAtLocation;
}

void FAnimNode_MySkeletalControl::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	FAnimNode_SkeletalControlBase::CacheBones_AnyThread(Context);
	LookAtNode.CacheBones_AnyThread(Context);
}

void FAnimNode_MySkeletalControl::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	LookAtNode.EvaluateSkeletalControl_AnyThread(Output, OutBoneTransforms);
}

bool FAnimNode_MySkeletalControl::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return TargetBone.IsValidToEvaluate(RequiredBones);
}

void FAnimNode_MySkeletalControl::UpdateInternal(const FAnimationUpdateContext& Context)
{
	FAnimNode_SkeletalControlBase::UpdateInternal(Context);
	LookAtNode.LookAtLocation = LookAtLocation;
	LookAtNode.UpdateInternal(Context);
}

void FAnimNode_MySkeletalControl::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	TargetBone.Initialize(RequiredBones);
}
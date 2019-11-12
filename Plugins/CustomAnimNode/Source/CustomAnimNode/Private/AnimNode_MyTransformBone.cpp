#include "AnimNode_MyTransformBone.h"
#include "CustomAnimNode.h"
#include "Animation/AnimInstanceProxy.h"

FAnimNode_MyTransformBone::FAnimNode_MyTransformBone()
	: LocalToComponentNode()
	, ModifyBoneNode()
	, ComponentToLocalNode()
{

}

void FAnimNode_MyTransformBone::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);

	//ƒm[ƒh‚ÌÚ‘±
	ComponentToLocalNode.ComponentPose.SetLinkNode(&ModifyBoneNode);
	ModifyBoneNode.ComponentPose.SetLinkNode(&LocalToComponentNode);
	LocalToComponentNode.LocalPose = SourcePose;

	//Transform(Modify) Bone ƒm[ƒh‚ÅRootBone‚ð­‚µã‚É‚ ‚°‚é
	ModifyBoneNode.BoneToModify.BoneName = FName("Root");
	ModifyBoneNode.BoneToModify.Initialize(Context.AnimInstanceProxy->GetSkeleton());
	ModifyBoneNode.Translation = FVector(0, 0, 100);
	ModifyBoneNode.TranslationMode = BMM_Replace;

	ComponentToLocalNode.Initialize_AnyThread(Context);
}

void FAnimNode_MyTransformBone::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentToLocalNode.CacheBones_AnyThread(Context);
}

void FAnimNode_MyTransformBone::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	ComponentToLocalNode.Update_AnyThread(Context);
}

void FAnimNode_MyTransformBone::Evaluate_AnyThread(FPoseContext& Output)
{
	ComponentToLocalNode.Evaluate_AnyThread(Output);
}
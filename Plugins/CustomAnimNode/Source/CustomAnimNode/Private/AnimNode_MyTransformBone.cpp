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

	//ノードの接続
	ComponentToLocalNode.ComponentPose.SetLinkNode(&ModifyBoneNode);
	ModifyBoneNode.ComponentPose.SetLinkNode(&LocalToComponentNode);
	LocalToComponentNode.LocalPose = SourcePose;

	//Transform(Modify) Bone ノードでRootBoneを少し上にあげる
	ModifyBoneNode.BoneToModify.BoneName = FName("Root");
	ModifyBoneNode.BoneToModify.Initialize(Context.AnimInstanceProxy->GetSkeleton());
	ModifyBoneNode.Translation = Translation;
	ModifyBoneNode.TranslationMode = TranslationMode;

	ComponentToLocalNode.Initialize_AnyThread(Context);
}

void FAnimNode_MyTransformBone::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentToLocalNode.CacheBones_AnyThread(Context);
}

void FAnimNode_MyTransformBone::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	//入力ピンを更新
	GetEvaluateGraphExposedInputs().Execute(Context);

	ComponentToLocalNode.Update_AnyThread(Context);
}

void FAnimNode_MyTransformBone::Evaluate_AnyThread(FPoseContext& Output)
{
	ComponentToLocalNode.Evaluate_AnyThread(Output);
}
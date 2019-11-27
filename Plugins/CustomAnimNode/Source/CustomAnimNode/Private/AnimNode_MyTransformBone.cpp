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

	//�m�[�h�̐ڑ�
	ComponentToLocalNode.ComponentPose.SetLinkNode(&ModifyBoneNode);
	ModifyBoneNode.ComponentPose.SetLinkNode(&LocalToComponentNode);
	LocalToComponentNode.LocalPose = SourcePose;

	//Transform(Modify) Bone �m�[�h��RootBone��������ɂ�����
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
	//���̓s�����X�V
	GetEvaluateGraphExposedInputs().Execute(Context);

	ComponentToLocalNode.Update_AnyThread(Context);
}

void FAnimNode_MyTransformBone::Evaluate_AnyThread(FPoseContext& Output)
{
	ComponentToLocalNode.Evaluate_AnyThread(Output);
}
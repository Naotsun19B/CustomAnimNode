#include "AnimNode_MyBlendAnim.h"
#include "CustomAnimNode.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimSequence.h"

FAnimNode_MyBlendAnimInternal::FAnimNode_MyBlendAnimInternal()
	: AnimNode_1()
	, AnimNode_2()
	, AnimNode_3()
{

}

void FAnimNode_MyBlendAnimInternal::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);
	AnimNode_1.Initialize_AnyThread(Context);
	AnimNode_2.Initialize_AnyThread(Context);
	AnimNode_3.Initialize_AnyThread(Context);
	AnimNode_1.Sequence = Animation_1;
	AnimNode_2.Sequence = Animation_2;
	AnimNode_3.Sequence = Animation_3;
}

void FAnimNode_MyBlendAnimInternal::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	AnimNode_1.UpdateAssetPlayer(Context);
	AnimNode_2.UpdateAssetPlayer(Context);
	AnimNode_3.UpdateAssetPlayer(Context);
}

void FAnimNode_MyBlendAnimInternal::Evaluate_AnyThread(FPoseContext& Output)
{
	const FBoneContainer* RequiredBones = &Output.AnimInstanceProxy->GetRequiredBones();

	/** 
	*	FCompactPose��FBlendedCurve�͎g�p����O��FBobeContainer�̕ϐ������������Ȃ���΂Ȃ�Ȃ�
	*	�������ɂ͂��ꂼ��ȉ��̊֐���p����
	*	FCompactPose	... SetBoneContatiner(const FBonecontainer*)
	*	FBlendedCurve	... InitFrom(const FBonecontainer&)
	**/

	//���͂���|�[�Y�p�̕ϐ���������
	FCompactPose pose_1;
	FCompactPose pose_2;
	FCompactPose pose_3;
	pose_1.SetBoneContainer(RequiredBones);
	pose_2.SetBoneContainer(RequiredBones);
	pose_3.SetBoneContainer(RequiredBones);

	//���͂���J�[�u�p�̕ϐ���������
	FBlendedCurve curve_1;
	FBlendedCurve curve_2;
	FBlendedCurve curve_3;
	curve_1.InitFrom(*RequiredBones);
	curve_2.InitFrom(*RequiredBones);
	curve_3.InitFrom(*RequiredBones);

	//�A�j���[�V�����̍Đ����Ԃ⃋�[�g���[�V�������g�����̕ϐ���������
	FAnimExtractContext context_1(AnimNode_1.GetAccumulatedTime(), Animation_1->bEnableRootMotion);
	FAnimExtractContext context_2(AnimNode_2.GetAccumulatedTime(), Animation_2->bEnableRootMotion);
	FAnimExtractContext context_3(AnimNode_3.GetAccumulatedTime(), Animation_3->bEnableRootMotion);

	//�o�͗p�̃|�[�Y�ƃJ�[�u�p�̕ϐ���������
	FCompactPose pose_1_2;
	FBlendedCurve curve_1_2;
	pose_1_2.SetBoneContainer(RequiredBones);
	curve_1_2.InitFrom(*RequiredBones);

	//�A�j���[�V�����̍Đ����Ԃ���|�[�Y�ƃJ�[�u���擾
	Animation_1->GetBonePose(pose_1, curve_1, context_1);
	Animation_2->GetBonePose(pose_2, curve_2, context_2);
	Animation_3->GetBonePose(pose_3, curve_3, context_3);
	
	//��̃A�j���[�V�������u�����h
	FAnimationRuntime::BlendTwoPosesTogether(
		pose_1, pose_2, curve_1, curve_2, 1 - Alpha_1, pose_1_2, curve_1_2
	);

	//�P��ڂ̌��ʂƎO�ڂ̃A�j���[�V�������u�����h
	FAnimationRuntime::BlendTwoPosesTogether(
		pose_1_2, pose_3, curve_1_2, curve_3, 1 - Alpha_2, Output.Pose, Output.Curve
	);
}

FAnimNode_MyBlendAnim::FAnimNode_MyBlendAnim()
	: InternalNode()
	, LayeredBoneBlendNode()
{

}

void FAnimNode_MyBlendAnim::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);

	InternalNode.AlphaBase = AlphaBase;
	InternalNode.Alpha_1 = Alpha_1;
	InternalNode.Alpha_2 = Alpha_2;
	InternalNode.Animation_1 = Animation_1;
	InternalNode.Animation_2 = Animation_2;
	InternalNode.Animation_3 = Animation_3;

	InternalNode.Initialize_AnyThread(Context);


	FBranchFilter branchFilter;
	branchFilter.BoneName = BoneToModify.BoneName;
	branchFilter.BlendDepth = 0;
	FInputBlendPose blendPose;
	blendPose.BranchFilters.Add(branchFilter);
	LayeredBoneBlendNode.LayerSetup.Add(blendPose);

	LayeredBoneBlendNode.BasePose = SourcePose;

	FPoseLink internalPose;
	internalPose.SetLinkNode(&InternalNode);
	internalPose.Initialize(Context);
	LayeredBoneBlendNode.BlendPoses.Add(internalPose);

	LayeredBoneBlendNode.BlendWeights.Add(AlphaBase);
	
	LayeredBoneBlendNode.Initialize_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	LayeredBoneBlendNode.CacheBones_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	LayeredBoneBlendNode.Update_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::Evaluate_AnyThread(FPoseContext& Output)
{
	LayeredBoneBlendNode.Evaluate_AnyThread(Output);
}
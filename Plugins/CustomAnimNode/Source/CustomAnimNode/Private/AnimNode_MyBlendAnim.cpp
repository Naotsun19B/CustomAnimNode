#include "AnimNode_MyBlendAnim.h"
#include "Animation/AnimInstanceProxy.h"

FAnimNode_MyBlendAnim::FAnimNode_MyBlendAnim()
	: InternalNode()
	, LayeredBoneBlendNode()
{

}

void FAnimNode_MyBlendAnim::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);

	BoneToModify.Initialize(Context.AnimInstanceProxy->GetRequiredBones());

	InternalNode.Animation_1 = Animation_1;
	InternalNode.Animation_2 = Animation_2;
	InternalNode.Animation_3 = Animation_3;

	InternalNode.Initialize_AnyThread(Context);

	//適用するボーンを設定
	FBranchFilter branchFilter;
	branchFilter.BoneName = BoneToModify.BoneName;
	branchFilter.BlendDepth = 0;
	FInputBlendPose blendPose;
	blendPose.BranchFilters.Add(branchFilter);
	LayeredBoneBlendNode.LayerSetup.Add(blendPose);

	LayeredBoneBlendNode.BasePose = SourcePose;

	//MyBlendAnimInternalノードとlayeredBoneBlendノードを接続
	FPoseLink internalPose;
	internalPose.SetLinkNode(&InternalNode);
	internalPose.Initialize(Context);
	LayeredBoneBlendNode.BlendPoses.Add(internalPose);

	LayeredBoneBlendNode.BlendWeights.Add(0.f);

	LayeredBoneBlendNode.Initialize_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	LayeredBoneBlendNode.CacheBones_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	//入力ピンを更新
	GetEvaluateGraphExposedInputs().Execute(Context);

	float isState2 = 0.f;
	float isState3 = 0.f;
	float alpha = 0.f;

	GetHandState(Context.GetDeltaTime(), isState2, isState3, alpha);

	InternalNode.IsState2 = isState2;
	InternalNode.IsState3 = isState3;
	LayeredBoneBlendNode.BlendWeights[0] = alpha;

	LayeredBoneBlendNode.Update_AnyThread(Context);
}

void FAnimNode_MyBlendAnim::Evaluate_AnyThread(FPoseContext& Output)
{
	LayeredBoneBlendNode.Evaluate_AnyThread(Output);
}

void FAnimNode_MyBlendAnim::GetHandState(float DeltaTime, float& IsState2, float& IsState3, float& Alpha)
{
	float targetIsState2 = (AnimState == EAnimState::AS_State2 ? 1.f : 0.f);
	float targetIsState3 = (AnimState == EAnimState::AS_State3 ? 1.f : 0.f);
	float targetAlpha = (AnimState == EAnimState::AS_Unknown ? 0.f : 1.f);

	IsState2 = FMath::FInterpTo(BeforeFrameIsState2, targetIsState2, DeltaTime, InterpSpeed);
	IsState3 = FMath::FInterpTo(BeforeFrameIsState3, targetIsState3, DeltaTime, InterpSpeed);
	Alpha = FMath::FInterpTo(BeforeFrameAlpha, targetAlpha, DeltaTime, InterpSpeed);

	BeforeFrameIsState2 = IsState2;
	BeforeFrameIsState3 = IsState3;
	BeforeFrameAlpha = Alpha;
}
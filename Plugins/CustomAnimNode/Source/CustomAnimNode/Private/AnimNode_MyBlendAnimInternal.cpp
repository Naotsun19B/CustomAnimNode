#include "AnimNode_MyBlendAnimInternal.h"
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
	if (Animation_1 == nullptr || Animation_2 == nullptr || Animation_3 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please specify all animation assets in ApplyHandState."));
		return;
	}

	const FBoneContainer* RequiredBones = &Output.AnimInstanceProxy->GetRequiredBones();

	/** 
	*	FCompactPoseとFBlendedCurveは使用する前にFBobeContainerの変数を初期化しなければならない
	*	初期化にはそれぞれ以下の関数を用いる
	*	FCompactPose	... SetBoneContatiner(const FBonecontainer*)
	*	FBlendedCurve	... InitFrom(const FBonecontainer&)
	**/

	//入力するポーズ用の変数を初期化
	FCompactPose pose_1;
	FCompactPose pose_2;
	FCompactPose pose_3;
	pose_1.SetBoneContainer(RequiredBones);
	pose_2.SetBoneContainer(RequiredBones);
	pose_3.SetBoneContainer(RequiredBones);

	//入力するカーブ用の変数を初期化
	FBlendedCurve curve_1;
	FBlendedCurve curve_2;
	FBlendedCurve curve_3;
	curve_1.InitFrom(*RequiredBones);
	curve_2.InitFrom(*RequiredBones);
	curve_3.InitFrom(*RequiredBones);

	//アニメーションの再生時間やルートモーションを使うかの変数を初期化
	FAnimExtractContext context_1(AnimNode_1.GetAccumulatedTime(), Animation_1->bEnableRootMotion);
	FAnimExtractContext context_2(AnimNode_2.GetAccumulatedTime(), Animation_2->bEnableRootMotion);
	FAnimExtractContext context_3(AnimNode_3.GetAccumulatedTime(), Animation_3->bEnableRootMotion);

	//出力用のポーズとカーブ用の変数を初期化
	FCompactPose pose_1_2;
	FBlendedCurve curve_1_2;
	pose_1_2.SetBoneContainer(RequiredBones);
	curve_1_2.InitFrom(*RequiredBones);

	//アニメーションの再生時間からポーズとカーブを取得
	Animation_1->GetBonePose(pose_1, curve_1, context_1);
	Animation_2->GetBonePose(pose_2, curve_2, context_2);
	Animation_3->GetBonePose(pose_3, curve_3, context_3);
	
	//二つのアニメーションをブレンド
	FAnimationRuntime::BlendTwoPosesTogether(
		pose_1, pose_2, curve_1, curve_2, 1 - IsState2, pose_1_2, curve_1_2
	);

	//１回目の結果と三つ目のアニメーションをブレンド
	FAnimationRuntime::BlendTwoPosesTogether(
		pose_1_2, pose_3, curve_1_2, curve_3, 1 - IsState3, Output.Pose, Output.Curve
	);
}

#include "NodeInfoParallel.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoParallel::NodeInfoParallel()
	: NodeInfo(NodeType::Parallel)
{
	mSuccessPolicy = BTPolicy::RequireOne;
	mFailurePolicy = BTPolicy::RequireOne;
}

void NodeInfoParallel::OnGUI()
{
	NodeInfo::OnGUI();

	const char* successPolicy = u8"一个成功就成功\0全部成功才成功\0";
	const char* failurePolicy = u8"一个失败就失败\0全部失败就失败\0";

	FormUtility::FormBegin("##NodeInfoSequence");
	FormUtility::FormCombo(u8"成功策略", (int*)&mSuccessPolicy, successPolicy);
	FormUtility::FormCombo(u8"失败策略", (int*)&mFailurePolicy, failurePolicy);
	FormUtility::FormEnd();
}
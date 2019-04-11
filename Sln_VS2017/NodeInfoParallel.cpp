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

const char* NodeInfoParallel::GetDescription() const
{
	return u8"多个子节点行为并行执行。\n>>需要自定义成功/失败规则。";
}

cJSON* NodeInfoParallel::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON_AddNumberToObject(self, "SuccessPolicy", (int)mSuccessPolicy);
	cJSON_AddNumberToObject(self, "FailurePolicy", (int)mFailurePolicy);

	SaveChildren(self);

	return self;
}

void NodeInfoParallel::Load(cJSON* self)
{
	NodeInfo::Load(self);

	mSuccessPolicy = (BTPolicy)cJSON_GetObjectItem(self, "SuccessPolicy")->valueint;
	mFailurePolicy = (BTPolicy)cJSON_GetObjectItem(self, "FailurePolicy")->valueint;
}
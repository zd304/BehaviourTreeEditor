#include "NodeInfoSequence.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSequence::NodeInfoSequence()
	: NodeInfo(NodeType::Sequence)
{
}

void NodeInfoSequence::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSequence");
	FormUtility::FormCheckBox(u8"循环顺序执行", &loop);
	FormUtility::FormEnd();
}

const char* NodeInfoSequence::GetDescription() const
{
	return u8"依次执行所有节点，直到其中一个失败则失败。\n>>如果全部执行成功则成功。\n>>如果全部执行失败则失败。";
}

cJSON* NodeInfoSequence::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON_AddBoolToObject(self, "Loop", loop);

	SaveChildren(self);

	return self;
}

void NodeInfoSequence::Load(cJSON* self)
{
	NodeInfo::Load(self);

	cJSON* item = cJSON_GetObjectItem(self, "Loop");
	if (item)
	{
		loop = (bool)item->valueint;
	}
}
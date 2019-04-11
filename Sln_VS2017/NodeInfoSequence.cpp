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
	FormUtility::FormEnd();
}

const char* NodeInfoSequence::GetDescription() const
{
	return u8"依次执行所有节点，直到其中一个失败则失败。\n>>如果全部执行成功则成功。\n>>如果全部执行失败则失败。";
}

cJSON* NodeInfoSequence::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	SaveChildren(self);

	return self;
}
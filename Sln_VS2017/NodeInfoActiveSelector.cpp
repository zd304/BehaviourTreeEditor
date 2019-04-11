#include "NodeInfoActiveSelector.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoActiveSelector::NodeInfoActiveSelector()
	: NodeInfo(NodeType::ActiveSelector)
{
}

void NodeInfoActiveSelector::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSequence");
	FormUtility::FormEnd();
}

const char* NodeInfoActiveSelector::GetDescription() const
{
	return u8"依次执行所有节点，直到其中一个失败则失败。\n>>如果全部执行成功则成功。\n>>如果全部执行失败则失败。\n如果[优先级更高的节点]执行成功或者[当前执行的节点]执行失败，则终止执行[当前执行的节点]。";
}

cJSON* NodeInfoActiveSelector::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	SaveChildren(self);

	return self;
}
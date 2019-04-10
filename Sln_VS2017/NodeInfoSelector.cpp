#include "NodeInfoSelector.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSelector::NodeInfoSelector()
	: NodeInfo(NodeType::Selector)
{
}

void NodeInfoSelector::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSelector");
	FormUtility::FormEnd();
}

const char* NodeInfoSelector::GetDescription() const
{
	return u8"依次执行每个子节点，直到其中一个执行成功\n如果全部执行失败则失败";
}

cJSON* NodeInfoSelector::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	SaveChildren(self);

	return self;
}
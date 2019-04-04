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

cJSON* NodeInfoSelector::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	SaveChildren(self);

	return self;
}
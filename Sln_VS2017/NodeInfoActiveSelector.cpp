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

cJSON* NodeInfoActiveSelector::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	SaveChildren(self);

	return self;
}
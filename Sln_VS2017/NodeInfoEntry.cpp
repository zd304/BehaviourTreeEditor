#include "NodeInfoEntry.h"

NodeInfoEntry::NodeInfoEntry()
	: NodeInfo(NodeType::Entry)
{

}

void NodeInfoEntry::OnGUI()
{
	NodeInfo::OnGUI();
}

const char* NodeInfoEntry::GetDescription() const
{
	return u8"行为树的起始节点，逻辑从这个节点开始向下执行。";
}

cJSON* NodeInfoEntry::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);
	
	SaveChildren(self);

	return self;
}
#include "NodeInfoEntry.h"

NodeInfoEntry::NodeInfoEntry()
	: NodeInfo(NodeType::Entry)
{

}

void NodeInfoEntry::OnGUI()
{
	NodeInfo::OnGUI();
}

cJSON* NodeInfoEntry::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);
	
	SaveChildren(self);

	return self;
}
#include "NodeInfoEntry.h"

NodeInfoEntry::NodeInfoEntry()
	: NodeInfo(NodeType::Entry)
{

}

void NodeInfoEntry::OnGUI()
{
	NodeInfo::OnGUI();
}
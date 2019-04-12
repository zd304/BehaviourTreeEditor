#include "EDNode.h"
#include "NodeInfo.h"
#include <algorithm>

EDNode::EDNode(int nodeID, const char* szName)
	: id(nodeID), name(szName), curOutput(0), maxOutput(INT_MAX), nodeInfo(NULL)
{

}

EDNode::~EDNode()
{
	inputPin.clear();
	outputPin.clear();

	if (parent != NULL)
	{
		for (std::vector<EDNode*>::iterator it = parent->children.begin();
			it != parent->children.end(); ++it)
		{
			EDNode* child = *it;
			if (!child || child != this) continue;
			parent->children.erase(it);
			break;
		}
		parent = NULL;
	}

	for (size_t i = 0; i < children.size(); ++i)
	{
		EDNode* child = children[i];
		if (!child) continue;
		child->parent = NULL;
	}

	SAFE_DELETE(nodeInfo);
}

bool CompEDNode(const EDNode* node1, const EDNode* node2)
{
	ImVec2 pos1 = ax::NodeEditor::GetNodePosition(node1->id);
	ImVec2 pos2 = ax::NodeEditor::GetNodePosition(node2->id);

	if (pos1.x < pos2.x)
		return true;
	return false;
}

void ResetNodeTreePos(EDNode* node, float diffHeight)
{
	std::vector<EDNode*> q;
	q.push_back(node);
	while (!q.empty())
	{
		std::vector<EDNode*>::iterator begin = q.begin();
		EDNode* t = *begin;

		if (t->parent)
		{
			ImVec2 parentPos = ax::NodeEditor::GetNodePosition(t->parent->id);
			ImVec2 childPos = ax::NodeEditor::GetNodePosition(t->id);

			childPos.y = parentPos.y + diffHeight;
			ax::NodeEditor::SetNodePosition(t->id, childPos);
		}

		q.erase(begin);
		std::sort(t->children.begin(), t->children.end(), CompEDNode);

		for (size_t i = 0; i < t->children.size(); ++i)
		{
			EDNode* child = t->children[i];
			q.push_back(child);
		}
	}
}

void BuildNode(EDNode* node)
{
	for (size_t i = 0; i < node->inputPin.size(); ++i)
	{
		EDPin* pin = &node->inputPin[i];
		pin->node = node;
		pin->kind = PinKind::Input;
	}

	for (size_t i = 0; i < node->outputPin.size(); ++i)
	{
		EDPin* pin = &node->outputPin[i];
		pin->node = node;
		pin->kind = PinKind::Output;
	}
}
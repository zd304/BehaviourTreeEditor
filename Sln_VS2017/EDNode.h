#pragma once

#include "EDPin.h"

namespace ed = ax::NodeEditor;

class EDNode
{
public:
	EDNode(int nodeID, const char* szName)
		: id(nodeID), name(szName)
	{

	}

	~EDNode()
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
	}
public:
	ed::NodeId id;
	std::string name;
	std::vector<EDPin> inputPin;
	std::vector<EDPin> outputPin;
public:
	EDNode* parent;
	std::vector<EDNode*> children;
};

static void ResetNodeTreePos(EDNode* node, float diffHeight)
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

		for (size_t i = 0; i < t->children.size(); ++i)
		{
			EDNode* child = t->children[i];
			q.push_back(child);
		}
	}
}

static void BuildNode(EDNode* node)
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
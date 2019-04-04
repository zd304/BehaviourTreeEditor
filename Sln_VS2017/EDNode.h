#pragma once

#include "EDPin.h"
#include "cJSON.h"

namespace ed = ax::NodeEditor;
class NodeInfo;

class EDNode
{
public:
	EDNode(int nodeID, const char* szName);

	~EDNode();
public:
	ed::NodeId id;
	std::string name;
	std::vector<EDPin> inputPin;
	std::vector<EDPin> outputPin;

	int curOutput;
	int maxOutput;
public:
	EDNode* parent;
	std::vector<EDNode*> children;
	NodeInfo* nodeInfo;
};

void ResetNodeTreePos(EDNode* node, float diffHeight);

void BuildNode(EDNode* node);
#pragma once

#include "Application.h"

enum NodeType
{
	Entry = 0,

	Selector = 1,
	ActiveSelector,
	Sequence,
	Parallel,
	RandomSelector,
	RandomSequence,

	Repeat = 101,
	Success,
	Inverter,

	MoveTo = 2001,
	PatrolRange,
	PatrolPath,
	SearchTarget,
};

extern std::map<NodeType, std::string> nodeTypeNames;

class NodeInfo
{
public:
	NodeInfo(NodeType type, const char* name = NULL);
	virtual void OnGUI();
public:
	NodeType mType;
	std::string mName;
};

void InitNodeTypeNames();
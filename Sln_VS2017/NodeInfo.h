#pragma once

#include "Application.h"
#include "cJSON.h"

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

class EDNode;

class NodeInfo
{
public:
	NodeInfo(NodeType type, const char* name = NULL);
	virtual void OnGUI();
	virtual cJSON* Save(cJSON* parentArray);
	virtual void Load(cJSON* self);
protected:
	void SaveChildren(cJSON* self);
public:
	NodeType mType;
	std::string mName;
	EDNode* mNode;
};

void InitNodeTypeNames();
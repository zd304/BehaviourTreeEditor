#pragma once

#include <map>

enum NodeType
{
	Entry = 0,

	Selector = 1,
	ActiveSelector,
	Sequence,
	Parallel,
	RandomSelector,
	RandomSequence,
	WeightRandomSelector,
	WeightRandomSequence,

	Repeat = 101,
	Success,
	Inverter,

	HaveTarget = 1001,
	IsUsingSkill,
	BoolCompare,
	IntCompare,
	FloatCompare,
	StringCompare,
	CharacterCompare,

	MoveTo = 2001,
	PatrolRange,
	PatrolPath,
	SearchTarget,
	CastSkill,
	Wait,
	SavePosition,
};

class EDNode;

typedef EDNode* (*CreateEDNodeFunc)(const char* name, int childCount);
typedef EDNode* (*CreateNodeFunc)(const char* name);

extern std::map<NodeType, CreateEDNodeFunc> createEDNodeFunc;
extern std::map<NodeType, std::string> nodeTypeNames;
extern std::map<NodeType, int> nodeChildCounts;
extern CreateNodeFunc createRootNodeFunc;
extern CreateNodeFunc createParentNodeFunc;
extern CreateNodeFunc createLeafNodeFunc;

void InitCreateNodeInfo();
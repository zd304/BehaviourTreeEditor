#pragma once

#include "NodeInfo.h"
#include "Variables.h"

enum SearchTargetType
{
	Passive,
	ActiveEnemy,
	ActiveFriend
};

enum SearchTargetCondition
{
	Nearest,
	Farest,
	HateHighest,
	LessHP,
	MostHP,
	Random
};

class NodeInfoSearchTarget : public NodeInfo
{
public:
	NodeInfoSearchTarget();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	SearchTargetType mSearchTargetType;
	SearchTargetCondition mSearchTargetCondition;
	VariableFloat mSearchDist;
};
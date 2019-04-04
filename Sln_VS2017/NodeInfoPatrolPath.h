#pragma once

#include "NodeInfo.h"
#include "Variables.h"

enum PatrolPathType
{
	Once,
	PingPong,
	Loop
};

class NodeInfoPatrolPath : public NodeInfo
{
public:
	NodeInfoPatrolPath();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	PatrolPathType patrolType;
	VariableString pathName;
};
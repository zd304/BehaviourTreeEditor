#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoPatrolRange : public NodeInfo
{
public:
	NodeInfoPatrolRange();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	VariableFloat range;
	VariableVector3 mCenter;
	float patrolMinInterval;
	float patrolMaxInterval;
};
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
public:
	PatrolPathType patrolType;
	VariableString pathName;
};
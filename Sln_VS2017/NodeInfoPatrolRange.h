#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoPatrolRange : public NodeInfo
{
public:
	NodeInfoPatrolRange();

	void OnGUI();
public:
	VariableFloat range;
};
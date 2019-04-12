#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoWait : public NodeInfo
{
public:
	NodeInfoWait();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	VariableFloat mWaitTime;
	VariableBool mRandomWaitTime;
	VariableFloat mMinWaitTime;
	VariableFloat mMaxWaitTime;
};
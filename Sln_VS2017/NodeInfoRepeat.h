#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoRepeat : public NodeInfo
{
public:
	NodeInfoRepeat();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	VariableInt repeatTime;
};
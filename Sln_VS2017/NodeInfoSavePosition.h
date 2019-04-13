#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoSavePosition : public NodeInfo
{
public:
	NodeInfoSavePosition();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	VariableVector3 position;
};
#pragma once

#include "NodeInfoCondition.h"

class NodeInfoIsUsingSkill : public NodeInfoCondition
{
public:
	NodeInfoIsUsingSkill();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	int skillID;
};
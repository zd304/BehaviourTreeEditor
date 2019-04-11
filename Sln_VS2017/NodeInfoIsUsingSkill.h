#pragma once

#include "NodeInfoCondition.h"

class NodeInfoIsUsingSkill : public NodeInfoCondition
{
public:
	NodeInfoIsUsingSkill();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
	const char* GetDescription() const;
public:
	int skillID;
};
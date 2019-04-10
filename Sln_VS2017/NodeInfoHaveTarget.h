#pragma once

#include "NodeInfoCondition.h"

enum BTTargetType
{
	All,
	Firend,
	Enemy,
};

class NodeInfoHaveTarget : public NodeInfoCondition
{
public:
	NodeInfoHaveTarget();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	BTTargetType targetType;
};
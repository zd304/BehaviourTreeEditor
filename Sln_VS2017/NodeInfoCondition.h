#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoCondition : public NodeInfo
{
public:
	NodeInfoCondition(NodeType type);

	virtual void OnGUI();
	virtual cJSON* Save(cJSON* parentArray);
	virtual void Load(cJSON* self);
public:
	bool mIsNegation;
};
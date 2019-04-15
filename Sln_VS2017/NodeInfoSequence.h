#pragma once

#include "NodeInfo.h"

class NodeInfoSequence : public NodeInfo
{
public:
	NodeInfoSequence();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
	const char* GetDescription() const;
public:
	bool loop;
};
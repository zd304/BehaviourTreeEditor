#pragma once

#include "NodeInfo.h"

class NodeInfoEntry : public NodeInfo
{
public:
	NodeInfoEntry();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	const char* GetDescription() const;
};
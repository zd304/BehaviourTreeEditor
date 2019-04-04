#pragma once

#include "NodeInfo.h"
#include "cJSON.h"

class NodeInfoActiveSelector : public NodeInfo
{
public:
	NodeInfoActiveSelector();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
};
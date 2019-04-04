#pragma once

#include "NodeInfo.h"

class NodeInfoSelector : public NodeInfo
{
public:
	NodeInfoSelector();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
};
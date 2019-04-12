#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoWait : public NodeInfo
{
public:
	NodeInfoWait();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	float mWaitTime;
	bool mRandomWaitTime;
	float mMinWaitTime;
	float mMaxWaitTime;
};
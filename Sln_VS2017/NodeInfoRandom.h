#pragma once

#include "NodeInfo.h"

class NodeInfoRandom : public NodeInfo
{
public:
	NodeInfoRandom(NodeType type);

	virtual void OnGUI();
	virtual cJSON* Save(cJSON* parentArray);
	virtual void Load(cJSON* self);
public:
	bool mUseSeed;
	int mSeed;
	int mExeCount;
};
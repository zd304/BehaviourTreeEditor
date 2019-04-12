#pragma once

#include "NodeInfoRandom.h"

class NodeInfoWeightRandomSelector : public NodeInfoRandom
{
public:
	NodeInfoWeightRandomSelector();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	std::vector<int> mWeights;
};
#pragma once

#include "NodeInfoRandom.h"

class NodeInfoWeightRandomSequence : public NodeInfoRandom
{
public:
	NodeInfoWeightRandomSequence();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	std::vector<int> mWeights;
};
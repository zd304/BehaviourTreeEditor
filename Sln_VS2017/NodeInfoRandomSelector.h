#pragma once

#include "NodeInfoRandom.h"

class NodeInfoRandomSelector : public NodeInfoRandom
{
public:
	NodeInfoRandomSelector();

	const char* GetDescription() const;
};
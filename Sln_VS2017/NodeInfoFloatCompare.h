#pragma once

#include "NodeInfoCompare.h"

class NodeInfoFloatCompare : public NodeInfoCompare
{
public:
	NodeInfoFloatCompare();

	const char* OpComboText() const;
};
#pragma once

#include "NodeInfoCompare.h"

class NodeInfoCharacterCompare : public NodeInfoCompare
{
public:
	NodeInfoCharacterCompare();

	const char* OpComboText() const;
};
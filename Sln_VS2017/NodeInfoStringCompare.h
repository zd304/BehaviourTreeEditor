#pragma once

#include "NodeInfoCompare.h"

class NodeInfoStringCompare : public NodeInfoCompare
{
public:
	NodeInfoStringCompare();

	const char* OpComboText() const;
};
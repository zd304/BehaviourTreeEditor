#pragma once

#include "NodeInfoCompare.h"

class NodeInfoBoolCompare : public NodeInfoCompare
{
public:
	NodeInfoBoolCompare();

	const char* OpComboText() const;
};
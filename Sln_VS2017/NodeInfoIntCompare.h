#pragma once

#include "NodeInfoCompare.h"

class NodeInfoIntCompare : public NodeInfoCompare
{
public:
	NodeInfoIntCompare();

	const char* OpComboText() const;
};
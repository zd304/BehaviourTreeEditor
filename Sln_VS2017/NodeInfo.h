#pragma once

#include "Application.h"

class NodeInfo
{
public:
	NodeInfo(NodeType type, const char* name = NULL);
	virtual void OnGUI();
public:
	NodeType mType;
	std::string mName;
};
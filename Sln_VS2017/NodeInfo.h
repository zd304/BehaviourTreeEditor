#pragma once

#include "Application.h"
#include "cJSON.h"
#include "NodeFactory.h"

class NodeInfo
{
public:
	NodeInfo(NodeType type, const char* name = NULL);
	virtual void OnGUI();
	virtual cJSON* Save(cJSON* parentArray);
	virtual void Load(cJSON* self);
protected:
	void SaveChildren(cJSON* self);
public:
	NodeType mType;
	std::string mName;
	EDNode* mNode;
};
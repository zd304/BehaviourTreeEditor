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
	virtual const char* GetDescription() const;
protected:
	void SaveChildren(cJSON* self);
public:
	NodeType mType;
	std::string mName;
	std::string mNote;
	EDNode* mNode;
};
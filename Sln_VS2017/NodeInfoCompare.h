#pragma once

#include "NodeInfoCondition.h"
#include "Variables.h"

enum BTCompareOp
{
	Equal,
	NotEqual,
	Less,
	LessEqual,
	More,
	MoreEqual
};

class NodeInfoCompare : public NodeInfoCondition
{
public:
	NodeInfoCompare(NodeType type, const char* label1, const char* label2);
	~NodeInfoCompare();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);

	virtual const char* OpComboText() const = 0;
public:
	Variable* v1;
	Variable* v2;
	std::string name1;
	std::string name2;

	BTCompareOp op;
};
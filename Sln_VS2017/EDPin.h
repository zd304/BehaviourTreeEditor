#pragma once

#include <string>
#include <vector>
#include "NodeEditor.h"

namespace ed = ax::NodeEditor;

class EDNode;

enum class PinKind
{
	Output,
	Input
};

struct EDPin
{
	ed::PinId id;
	std::string name;
	EDNode* node;
	PinKind kind;

	EDPin(int pinId, const char* szName)
		: id(pinId), name(szName)
	{

	}
};

static bool CanCreateLink(EDPin* a, EDPin* b)
{
	if (!a || !b || a == b || a->kind == b->kind || a->node == b->node)
	{
		return false;
	}
	return true;
}
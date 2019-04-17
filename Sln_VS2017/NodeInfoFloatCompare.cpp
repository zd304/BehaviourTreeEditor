#include "NodeInfoFloatCompare.h"

NodeInfoFloatCompare::NodeInfoFloatCompare()
	: NodeInfoCompare(NodeType::IntCompare, u8"浮点数1", u8"浮点数2")
{
	v1 = new VariableFloat();
	v2 = new VariableFloat();
}

const char* NodeInfoFloatCompare::OpComboText() const
{
	return u8"等于\0不等于\0小于\0小于等于\0大于\0大于等于\0";
}
#include "NodeInfoIntCompare.h"

NodeInfoIntCompare::NodeInfoIntCompare()
	: NodeInfoCompare(NodeType::IntCompare, u8"整数1", u8"整数2")
{
	v1 = new VariableInt();
	v2 = new VariableInt();
}

const char* NodeInfoIntCompare::OpComboText() const
{
	return u8"等于\0不等于\0小于\0小于等于\0大于\0大于等于\0";
}
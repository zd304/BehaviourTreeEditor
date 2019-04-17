#include "NodeInfoBoolCompare.h"

NodeInfoBoolCompare::NodeInfoBoolCompare()
	: NodeInfoCompare(NodeType::BoolCompare, u8"布尔值1", u8"布尔值2")
{
	v1 = new VariableBool();
	v2 = new VariableBool();
}

const char* NodeInfoBoolCompare::OpComboText() const
{
	return u8"等于\0不等于\0";
}
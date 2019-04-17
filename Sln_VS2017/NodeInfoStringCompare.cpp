#include "NodeInfoStringCompare.h"

NodeInfoStringCompare::NodeInfoStringCompare()
	: NodeInfoCompare(NodeType::StringCompare, u8"文字1", u8"文字2")
{
	v1 = new VariableString();
	v2 = new VariableString();
}

const char* NodeInfoStringCompare::OpComboText() const
{
	return u8"等于\0不等于\0";
}
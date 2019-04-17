#include "NodeInfoCharacterCompare.h"

NodeInfoCharacterCompare::NodeInfoCharacterCompare()
	: NodeInfoCompare(NodeType::CharacterCompare, u8"角色1", u8"角色2")
{
	v1 = new VariableCharacter();
	v2 = new VariableCharacter();
}

const char* NodeInfoCharacterCompare::OpComboText() const
{
	return u8"等于\0不等于\0";
}
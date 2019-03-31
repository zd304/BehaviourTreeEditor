#include "Variables.h"
#include "FormUtility.h"

VariableFloat::VariableFloat()
{
	type = VariableType::Float;
	value = 0.0f;
}

bool VariableFloat::OnGUI()
{
	if (FormUtility::FormFloat(name.c_str(), &value, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableInt::VariableInt()
{
	type = VariableType::Int;
	value = 0;
}

bool VariableInt::OnGUI()
{
	if (FormUtility::FormInt(name.c_str(), &value, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableBool::VariableBool()
{
	type = VariableType::Bool;
	value = true;
}

bool VariableBool::OnGUI()
{
	if (FormUtility::FormBool(name.c_str(), &value, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableString::VariableString()
{
	type = VariableType::String;
	memset(value, 0, TXT_SIZE);
}

bool VariableString::OnGUI()
{
	if (FormUtility::FormString(name.c_str(), (char*)&value, IM_ARRAYSIZE(value), u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableVector2::VariableVector2()
{
	type = VariableType::Vector2;
	memset(value, 0, 2 * sizeof(float));
}

bool VariableVector2::OnGUI()
{
	if (FormUtility::FormVector2(name.c_str(), value[0], value[1], u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableVector3::VariableVector3()
{
	type = VariableType::Vector3;
	memset(value, 0, 3 * sizeof(float));
}

bool VariableVector3::OnGUI()
{
	if (FormUtility::FormVector3(name.c_str(), value[0], value[1], value[2], u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableVector4::VariableVector4()
{
	type = VariableType::Vector4;
	memset(value, 0, 4 * sizeof(float));
}

bool VariableVector4::OnGUI()
{
	if (FormUtility::FormVector4(name.c_str(), value[0], value[1], value[2], value[3], u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableCharactor::VariableCharactor()
{
	type = VariableType::Charactor;
}

bool VariableCharactor::OnGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariablePlayer::VariablePlayer()
{
	type = VariableType::Player;
}

bool VariablePlayer::OnGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableNpc::VariableNpc()
{
	type = VariableType::Npc;
}

bool VariableNpc::OnGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableNeutralNpc::VariableNeutralNpc()
{
	type = VariableType::NeutralNpc;
}

bool VariableNeutralNpc::OnGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}

VariableMonster::VariableMonster()
{
	type = VariableType::Monster;
}

bool VariableMonster::OnGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"É¾³ý"))
	{
		return false;
	}
	return true;
}
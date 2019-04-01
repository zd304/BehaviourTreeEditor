#include "Variables.h"
#include "FormUtility.h"

Variable::Variable(VariableType _type)
	: type(_type), isValue(true), name(""), selectIndex(-1)
{
	
}

bool Variable::OnVariableCombo(const char* label)
{
	std::string comboTxt = "";
	std::vector<std::string> lsComboTxt;
	if (g_Variables.size() > 0)
	{
		for (int i = 0; i < g_Variables.size(); ++i)
		{
			Variable* var = g_Variables[i];
			if (var->type == type)
			{
				for (int j = 0; j < var->name.length(); ++j)
				{
					comboTxt.push_back(var->name[j]);
				}
				comboTxt.push_back('\0');
				
				lsComboTxt.push_back(var->name);
			}
		}
	}
	
	if (FormUtility::FormComboButton(label, &selectIndex, comboTxt.c_str(), -1, u8"转成值"))
	{
		isValue = true;
	}
	if (selectIndex >= 0 && selectIndex < lsComboTxt.size())
	{
		name = lsComboTxt[selectIndex];
	}

	return true;
}

VariableFloat::VariableFloat()
	: Variable(VariableType::Float)
{
	value = 0.0f;
}

bool VariableFloat::OnVariableGUI()
{
	if (FormUtility::FormFloat(name.c_str(), &value, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableFloat::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormFloat(label, &value, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableInt::VariableInt()
	: Variable(VariableType::Int)
{
	value = 0;
}

bool VariableInt::OnVariableGUI()
{
	if (FormUtility::FormInt(name.c_str(), &value, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableInt::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormInt(label, &value, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableBool::VariableBool()
	: Variable(VariableType::Bool)
{
	value = true;
}

bool VariableBool::OnVariableGUI()
{
	if (FormUtility::FormBool(name.c_str(), &value, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableBool::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormBool(label, &value, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableString::VariableString()
	: Variable(VariableType::String)
{
	memset(value, 0, TXT_SIZE);
}

bool VariableString::OnVariableGUI()
{
	if (FormUtility::FormString(name.c_str(), (char*)&value, IM_ARRAYSIZE(value), u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableString::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormString(label, value, TXT_SIZE, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableVector2::VariableVector2()
	: Variable(VariableType::Vector2)
{
	memset(value, 0, 2 * sizeof(float));
}

bool VariableVector2::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormVector2(label, value[0], value[1], u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

bool VariableVector2::OnVariableGUI()
{
	if (FormUtility::FormVector2(name.c_str(), value[0], value[1], u8"删除"))
	{
		return false;
	}
	return true;
}

VariableVector3::VariableVector3()
	: Variable(VariableType::Vector3)
{
	memset(value, 0, 3 * sizeof(float));
}

bool VariableVector3::OnVariableGUI()
{
	if (FormUtility::FormVector3(name.c_str(), value[0], value[1], value[2], u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableVector3::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		if (FormUtility::FormVector3(label, value[0], value[1], value[2], u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableVector4::VariableVector4()
	: Variable(VariableType::Vector4)
{
	memset(value, 0, 4 * sizeof(float));
}

bool VariableVector4::OnVariableGUI()
{
	if (FormUtility::FormVector4(name.c_str(), value[0], value[1], value[2], value[3], u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableVector4::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormVector4(label, value[0], value[1], value[2], value[3], u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableCharactor::VariableCharactor()
	: Variable(VariableType::Charactor)
{
}

bool VariableCharactor::OnVariableGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableCharactor::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormInt(label, &gid, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariablePlayer::VariablePlayer()
	: Variable(VariableType::Player)
{
}

bool VariablePlayer::OnVariableGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariablePlayer::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormInt(label, &gid, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableNpc::VariableNpc()
	: Variable(VariableType::Npc)
{
}

bool VariableNpc::OnVariableGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableNpc::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormInt(label, &gid, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableNeutralNpc::VariableNeutralNpc()
	: Variable(VariableType::NeutralNpc)
{
}

bool VariableNeutralNpc::OnVariableGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableNeutralNpc::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormInt(label, &gid, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}

VariableMonster::VariableMonster()
	: Variable(VariableType::Monster)
{
}

bool VariableMonster::OnVariableGUI()
{
	gid = 0;
	if (FormUtility::FormInt(name.c_str(), &gid, u8"删除"))
	{
		return false;
	}
	return true;
}

bool VariableMonster::OnInspectorGUI(const char* label, void* ptr)
{
	if (isValue)
	{
		ImVec4* p = (ImVec4*)ptr;
		if (FormUtility::FormInt(label, &gid, u8"转变量"))
		{
			isValue = false;
		}
	}
	else
	{
		OnVariableCombo(label);
	}
	return true;
}
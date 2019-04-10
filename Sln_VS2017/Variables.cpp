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
		for (size_t i = 0; i < g_Variables.size(); ++i)
		{
			Variable* var = g_Variables[i];
			if (var->type == type)
			{
				for (size_t j = 0; j < var->name.length(); ++j)
				{
					comboTxt.push_back(var->name[j]);
				}
				comboTxt.push_back('\0');

				if (var->name == name)
				{
					selectIndex = i;
				}
				
				lsComboTxt.push_back(var->name);
			}
		}
	}
	
	if (FormUtility::FormComboButton(label, &selectIndex, comboTxt.c_str(), -1, u8"转成值"))
	{
		isValue = true;
	}
	if (selectIndex >= 0 && (size_t)selectIndex < lsComboTxt.size())
	{
		name = lsComboTxt[selectIndex];
	}

	return true;
}

cJSON* Variable::ToJson()
{
	cJSON* var = cJSON_CreateObject();
	cJSON_AddStringToObject(var, "Name", name.c_str());
	cJSON_AddNumberToObject(var, "Type", (int)type);
	cJSON_AddBoolToObject(var, "IsValue", isValue);

	return var;
}

void Variable::Load(cJSON* json)
{
	name = cJSON_GetObjectItem(json, "Name")->valuestring;
	type = (VariableType)cJSON_GetObjectItem(json, "Type")->valueint;
	isValue = (bool)cJSON_GetObjectItem(json, "IsValue")->valueint;
	selectIndex = -1;
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

cJSON* VariableFloat::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", value);

	return var;
}

void VariableFloat::Load(cJSON* json)
{
	Variable::Load(json);
	value = (float)cJSON_GetObjectItem(json, "Value")->valuedouble;
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

cJSON* VariableInt::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", value);

	return var;
}

void VariableInt::Load(cJSON* json)
{
	Variable::Load(json);
	value = cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariableBool::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddBoolToObject(var, "Value", value);

	return var;
}

void VariableBool::Load(cJSON* json)
{
	Variable::Load(json);
	value = (bool)cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariableString::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddStringToObject(var, "Value", value);

	return var;
}

void VariableString::Load(cJSON* json)
{
	Variable::Load(json);
	std::string txt = cJSON_GetObjectItem(json, "Value")->valuestring;
	memset(value, 0, TXT_SIZE);
	memcpy(value, txt.c_str(), txt.length());
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

cJSON* VariableVector2::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON* v = cJSON_CreateArray();
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[0]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[1]));
	cJSON_AddItemToObject(var, "Value", v);

	return var;
}

void VariableVector2::Load(cJSON* json)
{
	Variable::Load(json);
	cJSON* v = cJSON_GetObjectItem(json, "Value");
	float x = (float)cJSON_GetArrayItem(v, 0)->valuedouble;
	float y = (float)cJSON_GetArrayItem(v, 1)->valuedouble;
	value[0] = x;
	value[1] = y;
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

cJSON* VariableVector3::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON* v = cJSON_CreateArray();
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[0]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[1]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[2]));
	cJSON_AddItemToObject(var, "Value", v);

	return var;
}

void VariableVector3::Load(cJSON* json)
{
	Variable::Load(json);
	cJSON* v = cJSON_GetObjectItem(json, "Value");
	float x = (float)cJSON_GetArrayItem(v, 0)->valuedouble;
	float y = (float)cJSON_GetArrayItem(v, 1)->valuedouble;
	float z = (float)cJSON_GetArrayItem(v, 2)->valuedouble;
	value[0] = x;
	value[1] = y;
	value[2] = z;
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

cJSON* VariableVector4::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON* v = cJSON_CreateArray();
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[0]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[1]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[2]));
	cJSON_AddItemToArray(v, cJSON_CreateNumber(value[3]));
	cJSON_AddItemToObject(var, "Value", v);

	return var;
}

void VariableVector4::Load(cJSON* json)
{
	Variable::Load(json);
	cJSON* v = cJSON_GetObjectItem(json, "Value");
	float x = (float)cJSON_GetArrayItem(v, 0)->valuedouble;
	float y = (float)cJSON_GetArrayItem(v, 1)->valuedouble;
	float z = (float)cJSON_GetArrayItem(v, 2)->valuedouble;
	float w = (float)cJSON_GetArrayItem(v, 3)->valuedouble;
	value[0] = x;
	value[1] = y;
	value[2] = z;
	value[3] = w;
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

cJSON* VariableCharactor::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", gid);

	return var;
}

void VariableCharactor::Load(cJSON* json)
{
	Variable::Load(json);
	gid = cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariablePlayer::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", gid);

	return var;
}

void VariablePlayer::Load(cJSON* json)
{
	Variable::Load(json);
	gid = cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariableNpc::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", gid);

	return var;
}

void VariableNpc::Load(cJSON* json)
{
	Variable::Load(json);
	gid = cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariableNeutralNpc::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", gid);

	return var;
}

void VariableNeutralNpc::Load(cJSON* json)
{
	Variable::Load(json);
	gid = cJSON_GetObjectItem(json, "Value")->valueint;
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

cJSON* VariableMonster::ToJson()
{
	cJSON* var = Variable::ToJson();
	cJSON_AddNumberToObject(var, "Value", gid);

	return var;
}

void VariableMonster::Load(cJSON* json)
{
	Variable::Load(json);
	gid = cJSON_GetObjectItem(json, "Value")->valueint;
}

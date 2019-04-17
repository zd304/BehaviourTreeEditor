#pragma once

#include <string>
#include <vector>
#include "imgui.h"
#include "cJSON.h"

enum VariableType
{
	Bool,
	Int,
	Float,
	String,
	Vector2,
	Vector3,
	Vector4,
	Charactor,
	Player,
	Npc,
	NeutralNpc,
	Monster,
};

class Variable;
static const char* g_VariableTypeTxts = u8"是否\0整数\0浮点数\0文字\0二维向量\0三维向量\0四维向量\0角色\0玩家\0NPC\0中立NPC\0怪物";
extern std::vector<Variable*> g_Variables;

class Variable
{
public:
	Variable(VariableType _type);

	virtual bool OnVariableGUI() = 0;
	virtual bool OnInspectorGUI(const char* label, bool set = false) = 0;
	virtual cJSON* ToJson();
	virtual void Load(cJSON* json);
protected:
	bool OnVariableCombo(const char* label, bool set);
public:
	std::string name;
	VariableType type;
public:
	bool isValue;
	int selectIndex;
};

class VariableFloat : public Variable
{
public:
	VariableFloat();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	float value;
};

class VariableInt : public Variable
{
public:
	VariableInt();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int value;
};

class VariableBool : public Variable
{
public:
	VariableBool();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	bool value;
};

class VariableString : public Variable
{
public:
	VariableString();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	static const int TXT_SIZE = 128;
	char value[TXT_SIZE];
};

class VariableVector2 : public Variable
{
public:
	VariableVector2();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	float value[2];
};

class VariableVector3 : public Variable
{
public:
	VariableVector3();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	float value[3];
};

class VariableVector4 : public Variable
{
public:
	VariableVector4();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	float value[4];
};

class VariableCharacter : public Variable
{
public:
	VariableCharacter();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int gid;
};

class VariablePlayer : public Variable
{
public:
	VariablePlayer();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int gid;
};

class VariableNpc : public Variable
{
public:
	VariableNpc();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int gid;
};

class VariableNeutralNpc : public Variable
{
public:
	VariableNeutralNpc();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int gid;
};

class VariableMonster : public Variable
{
public:
	VariableMonster();

	bool OnVariableGUI();
	bool OnInspectorGUI(const char* label, bool set = false);
	cJSON* ToJson();
	void Load(cJSON* json);
public:
	int gid;
};
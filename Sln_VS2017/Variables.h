#pragma once

#include <string>
#include "imgui.h"

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

static const char* g_VariableTypeTxts = u8"是否\0整数\0浮点数\0文字\0二维向量\0三维向量\0四维向量\0角色\0玩家\0NPC\0中立NPC\0怪物";

class Variable
{
public:
	virtual bool OnGUI() = 0;
public:
	bool isValue;
	std::string name;
	VariableType type;
};

class VariableFloat : public Variable
{
public:
	VariableFloat();

	bool OnGUI();
public:
	float value;
};

class VariableInt : public Variable
{
public:
	VariableInt();

	bool OnGUI();
public:
	int value;
};

class VariableBool : public Variable
{
public:
	VariableBool();

	bool OnGUI();
public:
	bool value;
};

class VariableString : public Variable
{
public:
	VariableString();

	bool OnGUI();
public:
	static const int TXT_SIZE = 128;
	char value[TXT_SIZE];
};

class VariableVector2 : public Variable
{
public:
	VariableVector2();

	bool OnGUI();
public:
	float value[2];
};

class VariableVector3 : public Variable
{
public:
	VariableVector3();

	bool OnGUI();
public:
	float value[3];
};

class VariableVector4 : public Variable
{
public:
	VariableVector4();

	bool OnGUI();
public:
	float value[4];
};

class VariableCharactor : public Variable
{
public:
	VariableCharactor();

	bool OnGUI();
public:
	int gid;
};

class VariablePlayer : public Variable
{
public:
	VariablePlayer();

	bool OnGUI();
public:
	int gid;
};

class VariableNpc : public Variable
{
public:
	VariableNpc();

	bool OnGUI();
public:
	int gid;
};

class VariableNeutralNpc : public Variable
{
public:
	VariableNeutralNpc();

	bool OnGUI();
public:
	int gid;
};

class VariableMonster : public Variable
{
public:
	VariableMonster();

	bool OnGUI();
public:
	int gid;
};
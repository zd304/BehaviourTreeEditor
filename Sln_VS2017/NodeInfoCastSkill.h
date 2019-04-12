#pragma once

#include "NodeInfo.h"
#include "Variables.h"

class NodeInfoCastSkill : public NodeInfo
{
public:
	NodeInfoCastSkill();

	void OnGUI();
	cJSON* Save(cJSON* parentArray);
	void Load(cJSON* self);
public:
	int mSkillID;
	bool mSpecifyTarget;
	VariableCharactor mSkillTarget;
	bool mSpecifyTargetPos;
	VariableVector3 mSkillTargetPos;
};
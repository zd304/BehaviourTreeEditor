#include "NodeInfoIsUsingSkill.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoIsUsingSkill::NodeInfoIsUsingSkill()
	: NodeInfoCondition(NodeType::IsUsingSkill), skillID(0)
{

}

void NodeInfoIsUsingSkill::OnGUI()
{
	NodeInfoCondition::OnGUI();

	bool specifySkill = skillID > 0;

	FormUtility::FormBegin("##NodeInfoCondition");
	FormUtility::FormCheckBox(u8"是否在放指定技能", &specifySkill);
	if (specifySkill)
	{
		FormUtility::FormInt(u8"技能ID", &skillID);
	}
	FormUtility::FormEnd();

	if (skillID <= 0 && specifySkill)
	{
		skillID = 1;
	}
	if (skillID > 0 && !specifySkill)
	{
		skillID = 0;
	}

	ImGui::Separator();
}

cJSON* NodeInfoIsUsingSkill::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfoCondition::Save(parentArray);

	cJSON_AddNumberToObject(self, "SkillID", skillID);

	return self;
}

void NodeInfoIsUsingSkill::Load(cJSON* self)
{
	NodeInfoCondition::Load(self);

	skillID = cJSON_GetObjectItem(self, "SkillID")->valueint;
}
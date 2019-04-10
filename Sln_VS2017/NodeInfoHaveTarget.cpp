#include "NodeInfoHaveTarget.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoHaveTarget::NodeInfoHaveTarget()
	: NodeInfoCondition(NodeType::HaveTarget), targetType(BTTargetType::All)
{

}

void NodeInfoHaveTarget::OnGUI()
{
	NodeInfoCondition::OnGUI();

	const char* targetTypeDesc = u8"所有角色\0友方\0敌方";

	FormUtility::FormBegin("##NodeInfoCondition");
	FormUtility::FormCombo(u8"目标类型", (int*)&targetType, targetTypeDesc);
	FormUtility::FormEnd();

	ImGui::Separator();
}

cJSON* NodeInfoHaveTarget::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfoCondition::Save(parentArray);

	cJSON_AddNumberToObject(self, "TargetType", targetType);

	return self;
}

void NodeInfoHaveTarget::Load(cJSON* self)
{
	NodeInfoCondition::Load(self);

	targetType = (BTTargetType)cJSON_GetObjectItem(self, "TargetType")->valueint;
}
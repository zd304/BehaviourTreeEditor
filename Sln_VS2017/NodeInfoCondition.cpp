#include "NodeInfoCondition.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoCondition::NodeInfoCondition(NodeType type)
	: NodeInfo(type)
{

}

void NodeInfoCondition::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoCondition");
	FormUtility::FormCheckBox(u8"ÊÇ·ñÈ¡·´", &mIsNegation);
	FormUtility::FormEnd();

	ImGui::Separator();
}

cJSON* NodeInfoCondition::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON_AddBoolToObject(self, "Neg", mIsNegation);

	return self;
}

void NodeInfoCondition::Load(cJSON* self)
{
	NodeInfo::Load(self);

	mIsNegation = (bool)cJSON_GetObjectItem(self, "Neg")->valueint;
}
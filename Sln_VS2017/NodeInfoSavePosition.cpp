#include "NodeInfoSavePosition.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSavePosition::NodeInfoSavePosition()
	: NodeInfo(NodeType::SavePosition)
{

}

void NodeInfoSavePosition::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoPatrolPath");
	position.OnInspectorGUI(u8"Œª÷√±‰¡ø", true);
	FormUtility::FormEnd();
}

cJSON* NodeInfoSavePosition::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON* jsonPosition = position.ToJson();
	cJSON_AddItemToObject(self, "SPos", jsonPosition);

	return self;
}

void NodeInfoSavePosition::Load(cJSON* self)
{
	NodeInfo::Load(self);

	cJSON* jsonPosition = cJSON_GetObjectItem(self, "SPos");
	position.Load(jsonPosition);
}
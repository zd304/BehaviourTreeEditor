#include "NodeInfoRepeat.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoRepeat::NodeInfoRepeat()
	: NodeInfo(NodeType::Repeat)
{

}

void NodeInfoRepeat::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoPatrolPath");
	repeatTime.OnInspectorGUI(u8"ÖØ¸´´ÎÊý");
	FormUtility::FormEnd();
}

cJSON* NodeInfoRepeat::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON* jsonRepeatTime = repeatTime.ToJson();
	cJSON_AddItemToObject(self, "Limited", jsonRepeatTime);

	return self;
}

void NodeInfoRepeat::Load(cJSON* self)
{
	NodeInfo::Load(self);

	cJSON* jsonRepeatTime = cJSON_GetObjectItem(self, "Limited");
	repeatTime.Load(jsonRepeatTime);
}
#include "NodeInfoPatrolRange.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoPatrolRange::NodeInfoPatrolRange()
	: NodeInfo(NodeType::PatrolRange)
{
	range.value = 0.0f;
}

void NodeInfoPatrolRange::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoPatrolRange");
	range.OnInspectorGUI(u8"巡逻范围", NULL);
	FormUtility::FormFloat(u8"最小间隔时间", &patrolMinInterval);
	FormUtility::FormFloat(u8"最大间隔时间", &patrolMaxInterval);
	FormUtility::FormEnd();
}

cJSON* NodeInfoPatrolRange::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON* jsonRange = range.ToJson();
	cJSON_AddItemToObject(self, "Range", jsonRange);
	cJSON_AddDoubleToObject(self, "MinItv", patrolMinInterval);
	cJSON_AddDoubleToObject(self, "MaxItv", patrolMaxInterval);

	return self;
}

void NodeInfoPatrolRange::Load(cJSON* self)
{
	NodeInfo::Load(self);

	cJSON* jsonRange = cJSON_GetObjectItem(self, "Range");
	range.Load(jsonRange);
	patrolMinInterval = (float)cJSON_GetObjectItem(self, "MinItv")->valuedouble;
	patrolMaxInterval = (float)cJSON_GetObjectItem(self, "MaxItv")->valuedouble;
}
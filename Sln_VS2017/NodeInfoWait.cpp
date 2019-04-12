#include "NodeInfoWait.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoWait::NodeInfoWait()
	: NodeInfo(NodeType::Wait), mWaitTime(0.0f), mRandomWaitTime(false),
	mMaxWaitTime(0.0f), mMinWaitTime(0.0f)
{

}

void NodeInfoWait::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoPatrolPath");
	FormUtility::FormCheckBox(u8"是否随机等待时间", &mRandomWaitTime);
	if (mRandomWaitTime)
	{
		FormUtility::FormFloat(u8"最小等待时间", &mMinWaitTime);
		FormUtility::FormFloat(u8"最大等待时间", &mMaxWaitTime);
	}
	else
	{
		FormUtility::FormFloat(u8"等待时间", &mWaitTime);
	}
	FormUtility::FormEnd();
}

cJSON* NodeInfoWait::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON_AddBoolToObject(self, "Random", mRandomWaitTime);
	if (mRandomWaitTime)
	{
		cJSON_AddDoubleToObject(self, "Min", mMinWaitTime);
		cJSON_AddDoubleToObject(self, "Max", mMaxWaitTime);
	}
	else
	{
		cJSON_AddDoubleToObject(self, "Time", mWaitTime);
	}

	return self;
}

void NodeInfoWait::Load(cJSON* self)
{
	NodeInfo::Load(self);

	mRandomWaitTime = (bool)cJSON_GetObjectItem(self, "Random")->valueint;
	if (mRandomWaitTime)
	{
		mMinWaitTime = (float)cJSON_GetObjectItem(self, "Min")->valuedouble;
		mMaxWaitTime = (float)cJSON_GetObjectItem(self, "Max")->valuedouble;
	}
	else
	{
		mWaitTime = (float)cJSON_GetObjectItem(self, "Time")->valuedouble;
	}
}
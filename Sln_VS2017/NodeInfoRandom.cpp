#include "NodeInfoRandom.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoRandom::NodeInfoRandom(NodeType type)
	: NodeInfo(type), mExeCount(-1), mUseSeed(false), mSeed(0)
{
}

void NodeInfoRandom::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoRandomSelector");
	FormUtility::FormCheckBox(u8"是否使用随机数种子", &mUseSeed);
	if (mUseSeed)
	{
		FormUtility::FormInt(u8"随机数种子", &mSeed);
	}
	FormUtility::FormInt(u8"执行节点数量", &mExeCount);
	FormUtility::FormEnd();
}

cJSON* NodeInfoRandom::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfo::Save(parentArray);

	cJSON_AddBoolToObject(self, "UseSeed", mUseSeed);
	cJSON_AddNumberToObject(self, "Seed", mSeed);
	cJSON_AddNumberToObject(self, "ExeCount", mExeCount);

	SaveChildren(self);

	return self;
}

void NodeInfoRandom::Load(cJSON* self)
{
	NodeInfo::Load(self);

	mUseSeed = (bool)cJSON_GetObjectItem(self, "UseSeed")->valueint;
	mSeed = cJSON_GetObjectItem(self, "Seed")->valueint;
	mExeCount = cJSON_GetObjectItem(self, "ExeCount")->valueint;
}
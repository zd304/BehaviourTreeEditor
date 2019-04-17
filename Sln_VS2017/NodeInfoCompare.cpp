#include "NodeInfoCompare.h"
#include "EDNode.h"
#include "FormUtility.h"

NodeInfoCompare::NodeInfoCompare(NodeType type, const char* label1, const char* label2)
	: NodeInfoCondition(type), name1(label1), name2(label2)
{
	v1 = NULL;
	v2 = NULL;
}

NodeInfoCompare::~NodeInfoCompare()
{
	SAFE_DELETE(v1);
	SAFE_DELETE(v2);
}

void NodeInfoCompare::OnGUI()
{
	NodeInfoCondition::OnGUI();

	FormUtility::FormBegin("##NodeInfoCompare");
	if (v1)
	{
		v1->OnInspectorGUI(name1.c_str());
		FormUtility::FormCombo(u8"¶Ô±È²Ù×÷·û", (int*)&op, OpComboText());
		v2->OnInspectorGUI(name2.c_str());
	}
	FormUtility::FormEnd();
}

cJSON* NodeInfoCompare::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfoCondition::Save(parentArray);

	if (!v1 || !v2)
		return NULL;
	cJSON_AddItemToObject(self, "V1", v1->ToJson());
	cJSON_AddItemToObject(self, "V2", v2->ToJson());
	cJSON_AddNumberToObject(self, "Op", (int)op);

	return self;
}

void NodeInfoCompare::Load(cJSON* self)
{
	NodeInfoCondition::Load(self);

	cJSON* jsonV1 = cJSON_GetObjectItem(self, "V1");
	if (jsonV1)
	{
		v1->Load(jsonV1);
	}
	cJSON* jsonV2 = cJSON_GetObjectItem(self, "V2");
	if (jsonV2)
	{
		v2->Load(jsonV2);
	}
	op = (BTCompareOp)cJSON_GetObjectItem(self, "Op")->valueint;
}
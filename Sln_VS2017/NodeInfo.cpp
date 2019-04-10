#include "NodeInfo.h"
#include "FormUtility.h"
#include "NodeInfos.h"
#include "EDNode.h"

NodeInfo::NodeInfo(NodeType type, const char* name)
	: mType(type)
{
	if (name == NULL)
	{
		auto it = nodeTypeNames.find(type);
		if (nodeTypeNames.end() == it)
			return;
		mName = it->second;
	}
	else
	{
		mName = name;
	}
}

void NodeInfo::OnGUI()
{
	FormUtility::FormBegin("##NodeInfoName");

	FormUtility::FormLabelText(u8"½ÚµãÃû³Æ", mName.c_str());

	FormUtility::FormEnd();

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}

cJSON* NodeInfo::Save(cJSON* parentArray)
{
	cJSON* node = cJSON_CreateObject();
	cJSON_AddNumberToObject(node, "Type", (int)mType);

	if (mNode)
	{
		ImVec2 vPos = ax::NodeEditor::GetNodePosition(mNode->id);

		cJSON* pos = cJSON_CreateArray();
		cJSON_AddItemToArray(pos, cJSON_CreateNumber(vPos.x));
		cJSON_AddItemToArray(pos, cJSON_CreateNumber(vPos.y));
		cJSON_AddItemToObject(node, "Pos", pos);
	}

	if (parentArray)
	{
		cJSON_AddItemToArray(parentArray, node);
	}

	return node;
}

void NodeInfo::Load(cJSON* self)
{
	mType = (NodeType)cJSON_GetObjectItem(self, "Type")->valueint;
}

void NodeInfo::SaveChildren(cJSON* self)
{
	cJSON* children = cJSON_CreateArray();
	cJSON_AddItemToObject(self, "Children", children);

	for (size_t i = 0; i < mNode->children.size(); ++i)
	{
		EDNode* child = mNode->children[i];
		child->nodeInfo->Save(children);
	}
}
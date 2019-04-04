#include "NodeInfo.h"
#include "FormUtility.h"
#include "NodeInfos.h"
#include "EDNode.h"

std::map<NodeType, std::string> nodeTypeNames;

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

	if (parentArray)
	{
		cJSON_AddItemToArray(parentArray, node);
	}

	return node;
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
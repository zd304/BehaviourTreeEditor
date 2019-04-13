#include "NodeInfo.h"
#include "FormUtility.h"
#include "NodeInfos.h"
#include "EDNode.h"

NodeInfo::NodeInfo(NodeType type, const char* name)
	: mType(type), mNote("")
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
	const char* desc = GetDescription();
	if (desc)
	{
		ImGui::PushTextWrapPos(leftViewWidth);
		ImGui::PushStyleColor(ImGuiCol_Text, 0xff99aaff);
		FormUtility::FormLabelText(u8"ÃèÊö", desc);
		ImGui::PopStyleColor();
		ImGui::PopTextWrapPos();
	}

	char note[256];
	memset(note, 0, 256);
	memcpy(note, mNote.c_str(), 256);
	FormUtility::FormTextMultiline(u8"×¢ÊÍ", note, 256, ImVec2(160.0f, 50.0f));
	mNote = note;

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
		cJSON_AddItemToArray(pos, cJSON_CreateDouble(vPos.x));
		cJSON_AddItemToArray(pos, cJSON_CreateDouble(vPos.y));
		cJSON_AddItemToObject(node, "Pos", pos);
		cJSON_AddStringToObject(node, "Note", mNote.c_str());
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
	mNote = cJSON_GetObjectItem(self, "Note")->valuestring;
}

const char* NodeInfo::GetDescription() const
{
	return NULL;
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
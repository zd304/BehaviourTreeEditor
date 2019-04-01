#include "NodeInfo.h"
#include "FormUtility.h"
#include "NodeInfos.h"

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
#include "NodeGUI.h"
#include "EDNode.h"
#include "FormUtility.h"
#include "Variables.h"

namespace ed = ax::NodeEditor;
FindNodeFunc findNodeFunc = NULL;

void SetNodeFindFunc(FindNodeFunc func)
{
	findNodeFunc = func;
}

EDNode* CreateNode(NodeType nodeType)
{
	auto it = nodeTypeNames.find(nodeType);
	if (it == nodeTypeNames.end())
	{
		return NULL;
	}

	EDNode* node = CreateNode(nodeType, it->second.c_str());
	
	return node;
}

Variable* CreateVariable(VariableType varType)
{
	Variable* var = NULL;
	switch (varType)
	{
	case VariableType::Bool:
	{
		var = new VariableBool();
	}
	break;
	case VariableType::Float:
	{
		var = new VariableFloat();
	}
	break;
	case VariableType::Int:
	{
		var = new VariableInt();
	}
	break;
	case VariableType::String:
	{
		var = new VariableString();
	}
	break;
	case VariableType::Vector2:
	{
		var = new VariableVector2();
	}
	break;
	case VariableType::Vector3:
	{
		var = new VariableVector3();
	}
	break;
	case VariableType::Vector4:
	{
		var = new VariableVector4();
	}
	break;
	case VariableType::Charactor:
	{
		var = new VariableCharacter();
	}
	break;
	case VariableType::Npc:
	{
		var = new VariableNpc();
	}
	break;
	case VariableType::NeutralNpc:
	{
		var = new VariableNeutralNpc();
	}
	break;
	case VariableType::Player:
	{
		var = new VariablePlayer();
	}
	break;
	case VariableType::Monster:
	{
		var = new VariableMonster();
	}
	break;
	}
	return var;
}

void OnInspector()
{
	std::vector<ed::NodeId> selectedNodes;
	selectedNodes.resize(ed::GetSelectedObjectCount());
	int nodeCount = ed::GetSelectedNodes(selectedNodes.data(), static_cast<int>(selectedNodes.size()));
	selectedNodes.resize(nodeCount);

	if (nodeCount > 0)
	{
		ed::NodeId curNodeId = selectedNodes[0];
		EDNode* node = findNodeFunc(curNodeId);
		if (node == NULL)
			return;

		if (node->nodeInfo != NULL)
		{
			node->nodeInfo->OnGUI();
		}
	}
}

void OnVarialbleGUI(std::vector<Variable*>& vars)
{
	FormUtility::FormBegin("##VarialbleGUI");

	FormUtility::FormLabelText(u8"提示", u8"暂不支持中文输入");

	static VariableType type;
	FormUtility::FormCombo(u8"变量类型", (int*)&type, g_VariableTypeTxts);

	static char variableName[128] = "";
	FormUtility::FormInputText(u8"变量名称", variableName, 128);

	FormUtility::FormEnd();

	if (ImGui::Button(u8"添加变量"))
	{
		Variable* var = CreateVariable(type);
		var->name = variableName;
		vars.push_back(var);
	}

	ImGui::Separator();

	FormUtility::FormBegin("##VarialbleGUI1");
	for (auto it = vars.begin(); it != vars.end(); ++it)
	{
		Variable* var = *it;
		if (var == NULL)
			continue;
		if (!var->OnVariableGUI())
		{
			vars.erase(it);
			break;
		}
	}
	FormUtility::FormEnd();
}
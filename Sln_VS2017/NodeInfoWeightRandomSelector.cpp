#include "NodeInfoWeightRandomSelector.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoWeightRandomSelector::NodeInfoWeightRandomSelector()
	: NodeInfoRandom(NodeType::WeightRandomSelector)
{
}

void NodeInfoWeightRandomSelector::OnGUI()
{
	NodeInfoRandom::OnGUI();

	if (mWeights.size() != mNode->children.size())
	{
		std::vector<int> oldWeights(mWeights);
		mWeights.clear();
		size_t size = __min(oldWeights.size(), mNode->children.size());
		size_t i = 0;
		for (i = 0; i < size; ++i)
		{
			mWeights.push_back(oldWeights[i]);
		}
		while (i < mNode->children.size())
		{
			mWeights.push_back(0);
			++i;
		}
	}
	bool collapse = ImGui::CollapsingHeader(u8"执行几率权重", ImGuiTreeNodeFlags_DefaultOpen);
	if (collapse)
	{
		ImGui::Indent(12.0f);

		FormUtility::FormBegin("##NodeInfoWeightRandomSelector");
		for (size_t i = 0; i < mNode->children.size(); ++i)
		{
			EDNode* node = mNode->children[i];
			FormUtility::FormInt(node->name.c_str(), &mWeights[i]);
		}
		FormUtility::FormEnd();

		ImGui::Unindent();
	}
}

cJSON* NodeInfoWeightRandomSelector::Save(cJSON* parentArray)
{
	cJSON* self = NodeInfoRandom::Save(parentArray);

	cJSON* weights = cJSON_CreateArray();
	cJSON_AddItemToObject(self, "Weights", weights);
	for (size_t i = 0; i < mWeights.size(); ++i)
	{
		cJSON_AddItemToArray(self, cJSON_CreateNumber(mWeights[i]));
	}

	return self;
}

void NodeInfoWeightRandomSelector::Load(cJSON* self)
{
	NodeInfoRandom::Load(self);

	mWeights.clear();
	cJSON* weights = cJSON_GetObjectItem(self, "Weights");
	int size = cJSON_GetArraySize(weights);
	for (int i = 0; i < size; ++i)
	{
		int w = cJSON_GetArrayItem(weights, i)->valueint;
		mWeights.push_back(w);
	}
}
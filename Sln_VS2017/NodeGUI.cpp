#include "NodeGUI.h"
#include "EDNode.h"
#include "NodeInfos.h"

namespace ed = ax::NodeEditor;
FindNodeFunc findNodeFunc = NULL;
CreateNodeFunc createParentNodeFunc = NULL;
CreateNodeFunc createChildNodeFunc = NULL;

void SetCreateParentNodeFunc(CreateNodeFunc func)
{
	createParentNodeFunc = func;
}

void SetCreateChildNodeFunc(CreateNodeFunc func)
{
	createChildNodeFunc = func;
}

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

	EDNode* node = NULL;
	switch (nodeType)
	{
	case NodeType::Selector:
	{
		node = createParentNodeFunc(it->second.c_str());
		node->nodeInfo = new NodeInfoSelector();
	}
	break;
	case NodeType::Sequence:
	{
		node = createParentNodeFunc(it->second.c_str());
		node->nodeInfo = new NodeInfoSequence();
	}
	break;
	}
	return node;
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
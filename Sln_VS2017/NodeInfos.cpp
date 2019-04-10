#include "NodeInfos.h"
#include "EDNode.h"

CreateNodeFunc createRootNodeFunc = NULL;
CreateNodeFunc createParentNodeFunc = NULL;
CreateNodeFunc createLeafNodeFunc = NULL;

void SetCreateRootNodeFunc(CreateNodeFunc func)
{
	createRootNodeFunc = func;
}

void SetCreateParentNodeFunc(CreateNodeFunc func)
{
	createParentNodeFunc = func;
}

void SetCreateLeafNodeFunc(CreateNodeFunc func)
{
	createLeafNodeFunc = func;
}

EDNode* CreateNode(NodeType nodeType, const char* name)
{
	EDNode* node = NULL;

	auto itf = createEDNodeFunc.find(nodeType);
	if (itf == createEDNodeFunc.end())
		return NULL;
	auto itc = nodeChildCounts.find(nodeType);
	if (itc == nodeChildCounts.end())
		return NULL;

	CreateEDNodeFunc createFunc = itf->second;
	int count = itc->second;

	node = createFunc(name, count);

	if (node && node->nodeInfo)
	{
		node->nodeInfo->mNode = node;
	}
	return node;
}
#include "NodeInfos.h"
#include "EDNode.h"

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

EDNode* CreateNode(NodeType nodeType, const char* name)
{
	EDNode* node = NULL;
	switch (nodeType)
	{
	case NodeType::Selector:
	{
		node = createParentNodeFunc(name);
		node->nodeInfo = new NodeInfoSelector();
	}
	break;
	case NodeType::Sequence:
	{
		node = createParentNodeFunc(name);
		node->nodeInfo = new NodeInfoSequence();
	}
	break;
	case NodeType::Parallel:
	{
		node = createParentNodeFunc(name);
		node->nodeInfo = new NodeInfoParallel();
	}
	break;
	case NodeType::PatrolRange:
	{
		node = createChildNodeFunc(name);
		node->nodeInfo = new NodeInfoPatrolRange();
	}
	break;
	case NodeType::PatrolPath:
	{
		node = createChildNodeFunc(name);
		node->nodeInfo = new NodeInfoPatrolPath();
	}
	break;
	case NodeType::SearchTarget:
	{
		node = createChildNodeFunc(name);
		node->nodeInfo = new NodeInfoSearchTarget();
	}
	break;
	}
	return node;
}
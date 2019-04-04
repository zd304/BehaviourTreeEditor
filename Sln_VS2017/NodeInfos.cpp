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

void InitNodeTypeNames()
{
	nodeTypeNames[NodeType::Entry] = u8"开始";

	nodeTypeNames[NodeType::Selector] = u8"选择节点";
	nodeTypeNames[NodeType::ActiveSelector] = u8"主动选择节点";
	nodeTypeNames[NodeType::Sequence] = u8"顺序节点";
	nodeTypeNames[NodeType::Parallel] = u8"并行节点";
	nodeTypeNames[NodeType::RandomSelector] = u8"随机选择节点";
	nodeTypeNames[NodeType::RandomSequence] = u8"随机顺序节点";

	nodeTypeNames[NodeType::Repeat] = u8"重复节点";
	nodeTypeNames[NodeType::Success] = u8"成功节点";
	nodeTypeNames[NodeType::Inverter] = u8"逆变节点";

	nodeTypeNames[NodeType::PatrolRange] = u8"范围巡逻";
	nodeTypeNames[NodeType::PatrolPath] = u8"路径巡逻";
	nodeTypeNames[NodeType::SearchTarget] = u8"搜寻目标";
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
	case NodeType::ActiveSelector:
	{
		node = createParentNodeFunc(name);
		node->nodeInfo = new NodeInfoActiveSelector();
	}
	break;
	}
	if (node->nodeInfo)
	{
		node->nodeInfo->mNode = node;
	}
	return node;
}
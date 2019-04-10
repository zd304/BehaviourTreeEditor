#include "NodeFactory.h"
#include "NodeInfos.h"
#include "EDNode.h"

#define DefCreateNodeFunc(className) EDNode* Create##className(const char* name, int childCount)\
	{\
		EDNode* node = NULL;\
		if (childCount == 0)\
		{\
			node = createLeafNodeFunc(name);\
		}\
		else if (childCount < 0)\
		{\
			node = createRootNodeFunc(name);\
		}\
		else\
		{\
			node = createParentNodeFunc(name);\
		}\
		node->nodeInfo = new className();\
		node->maxOutput = abs(childCount);\
		return node;\
	}

#define AddCreateNodeFunc(nodeType, className, name, childCount) createEDNodeFunc[nodeType] = Create##className;\
	nodeTypeNames[nodeType] = u8###name;\
	nodeChildCounts[nodeType] = childCount;

std::map<NodeType, std::string> nodeTypeNames;
std::map<NodeType, CreateEDNodeFunc> createEDNodeFunc;
std::map<NodeType, int> nodeChildCounts;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 复合节点;
DefCreateNodeFunc(NodeInfoSelector)
DefCreateNodeFunc(NodeInfoActiveSelector)
DefCreateNodeFunc(NodeInfoSequence)
DefCreateNodeFunc(NodeInfoParallel)
// 修饰节点;
// 条件节点;
// 行为节点;
DefCreateNodeFunc(NodeInfoPatrolRange)
DefCreateNodeFunc(NodeInfoPatrolPath)
DefCreateNodeFunc(NodeInfoSearchTarget)

void InitCreateNodeInfo()
{
	AddCreateNodeFunc(NodeType::Entry,				NodeInfoSelector,			开始,						-1);

	AddCreateNodeFunc(NodeType::Selector,			NodeInfoSelector,			选择节点,					INT_MAX);
	AddCreateNodeFunc(NodeType::ActiveSelector,		NodeInfoActiveSelector,		主动选择节点,				INT_MAX);
	AddCreateNodeFunc(NodeType::Sequence,			NodeInfoSequence,			顺序节点,					INT_MAX);
	AddCreateNodeFunc(NodeType::Parallel,			NodeInfoParallel,			并行节点,					INT_MAX);

	AddCreateNodeFunc(NodeType::PatrolRange,		NodeInfoPatrolRange,		范围巡逻,					0);
	AddCreateNodeFunc(NodeType::PatrolPath,			NodeInfoPatrolPath,			路径巡逻,					0);
	AddCreateNodeFunc(NodeType::SearchTarget,		NodeInfoSearchTarget,		搜寻目标,					0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
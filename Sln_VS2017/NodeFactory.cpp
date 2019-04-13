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

#define RegisterNode(nodeType, className, name, childCount) createEDNodeFunc[nodeType] = Create##className;\
	nodeTypeNames[nodeType] = u8###name;\
	nodeChildCounts[nodeType] = childCount;

std::map<NodeType, std::string> nodeTypeNames;
std::map<NodeType, CreateEDNodeFunc> createEDNodeFunc;
std::map<NodeType, int> nodeChildCounts;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DefCreateNodeFunc(NodeInfoEntry)
// 复合节点;
DefCreateNodeFunc(NodeInfoSelector)
DefCreateNodeFunc(NodeInfoActiveSelector)
DefCreateNodeFunc(NodeInfoSequence)
DefCreateNodeFunc(NodeInfoParallel)
DefCreateNodeFunc(NodeInfoRandomSelector)
DefCreateNodeFunc(NodeInfoRandomSequence)
DefCreateNodeFunc(NodeInfoWeightRandomSelector)
DefCreateNodeFunc(NodeInfoWeightRandomSequence)
// 修饰节点;
DefCreateNodeFunc(NodeInfoRepeat)
// 条件节点;
DefCreateNodeFunc(NodeInfoHaveTarget)
DefCreateNodeFunc(NodeInfoIsUsingSkill)
// 行为节点;
DefCreateNodeFunc(NodeInfoPatrolRange)
DefCreateNodeFunc(NodeInfoPatrolPath)
DefCreateNodeFunc(NodeInfoSearchTarget)
DefCreateNodeFunc(NodeInfoCastSkill)
DefCreateNodeFunc(NodeInfoWait)
DefCreateNodeFunc(NodeInfoSavePosition)

void InitCreateNodeInfo()
{
	RegisterNode(NodeType::Entry,				NodeInfoEntry,				开始,						-1);

	RegisterNode(NodeType::Selector,			NodeInfoSelector,			选择节点,					INT_MAX);
	RegisterNode(NodeType::ActiveSelector,		NodeInfoActiveSelector,		主动选择节点,				INT_MAX);
	RegisterNode(NodeType::Sequence,			NodeInfoSequence,			顺序节点,					INT_MAX);
	RegisterNode(NodeType::Parallel,			NodeInfoParallel,			并行节点,					INT_MAX);
	RegisterNode(NodeType::RandomSelector,		NodeInfoRandomSelector,		随机选择节点,				INT_MAX);
	RegisterNode(NodeType::RandomSequence,		NodeInfoRandomSequence,		随机顺序节点,				INT_MAX);
	RegisterNode(NodeType::WeightRandomSelector, NodeInfoWeightRandomSelector, 权重选择节点,			INT_MAX);
	RegisterNode(NodeType::WeightRandomSequence, NodeInfoWeightRandomSequence, 权重顺序节点,			INT_MAX);

	RegisterNode(NodeType::Repeat,				NodeInfoRepeat,				重复节点,					1);

	RegisterNode(NodeType::HaveTarget,			NodeInfoHaveTarget,			是否有目标,					0);
	RegisterNode(NodeType::IsUsingSkill,		NodeInfoIsUsingSkill,		是否在放技能,				0);

	RegisterNode(NodeType::PatrolRange,			NodeInfoPatrolRange,		范围巡逻,					0);
	RegisterNode(NodeType::PatrolPath,			NodeInfoPatrolPath,			路径巡逻,					0);
	RegisterNode(NodeType::SearchTarget,		NodeInfoSearchTarget,		搜寻目标,					0);
	RegisterNode(NodeType::CastSkill,			NodeInfoCastSkill,			施放技能,					0);
	RegisterNode(NodeType::Wait,				NodeInfoWait,				等待,						0);
	RegisterNode(NodeType::SavePosition,		NodeInfoSavePosition,		保存位置,					0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
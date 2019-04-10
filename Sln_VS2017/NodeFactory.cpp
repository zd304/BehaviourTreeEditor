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

// ���Ͻڵ�;
DefCreateNodeFunc(NodeInfoSelector)
DefCreateNodeFunc(NodeInfoActiveSelector)
DefCreateNodeFunc(NodeInfoSequence)
DefCreateNodeFunc(NodeInfoParallel)
// ���νڵ�;
DefCreateNodeFunc(NodeInfoRepeat)
// �����ڵ�;
DefCreateNodeFunc(NodeInfoHaveTarget)
DefCreateNodeFunc(NodeInfoIsUsingSkill)
// ��Ϊ�ڵ�;
DefCreateNodeFunc(NodeInfoPatrolRange)
DefCreateNodeFunc(NodeInfoPatrolPath)
DefCreateNodeFunc(NodeInfoSearchTarget)

void InitCreateNodeInfo()
{
	RegisterNode(NodeType::Entry,				NodeInfoSelector,			��ʼ,						-1);

	RegisterNode(NodeType::Selector,			NodeInfoSelector,			ѡ��ڵ�,					INT_MAX);
	RegisterNode(NodeType::ActiveSelector,		NodeInfoActiveSelector,		����ѡ��ڵ�,				INT_MAX);
	RegisterNode(NodeType::Sequence,			NodeInfoSequence,			˳��ڵ�,					INT_MAX);
	RegisterNode(NodeType::Parallel,			NodeInfoParallel,			���нڵ�,					INT_MAX);

	RegisterNode(NodeType::Repeat,				NodeInfoRepeat,				�ظ��ڵ�,					1);

	RegisterNode(NodeType::HaveTarget,			NodeInfoHaveTarget,			�Ƿ���Ŀ��,					0);
	RegisterNode(NodeType::IsUsingSkill,		NodeInfoIsUsingSkill,		�Ƿ��ڷż���,				0);

	RegisterNode(NodeType::PatrolRange,			NodeInfoPatrolRange,		��ΧѲ��,					0);
	RegisterNode(NodeType::PatrolPath,			NodeInfoPatrolPath,			·��Ѳ��,					0);
	RegisterNode(NodeType::SearchTarget,		NodeInfoSearchTarget,		��ѰĿ��,					0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
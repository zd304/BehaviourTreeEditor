#include "NodeInfoRandomSelector.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoRandomSelector::NodeInfoRandomSelector()
	: NodeInfoRandom(NodeType::RandomSelector)
{
}

const char* NodeInfoRandomSelector::GetDescription() const
{
	return u8"随机执行每个子节点，直到其中一个执行成功。\n>>如果一个执行成功则成功。\n>>如果全部执行失败则失败。";
}
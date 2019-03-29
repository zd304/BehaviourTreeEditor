#include "Application.h"
#include <Windows.h>

std::map<NodeType, std::string> nodeTypeNames;

void InitNodeTypeNames()
{
	nodeTypeNames[NodeType::Entry] = u8"开始";

	nodeTypeNames[NodeType::Selector] = u8"选择节点";
	nodeTypeNames[NodeType::Sequence] = u8"顺序节点";
	nodeTypeNames[NodeType::Parallel] = u8"并行节点";
	nodeTypeNames[NodeType::RandomSelector] = u8"随机选择节点";
	nodeTypeNames[NodeType::RandomSequence] = u8"随机顺序节点";

	nodeTypeNames[NodeType::Repeat] = u8"重复节点";
	nodeTypeNames[NodeType::Success] = u8"成功节点";
	nodeTypeNames[NodeType::Inverter] = u8"逆变节点";
}
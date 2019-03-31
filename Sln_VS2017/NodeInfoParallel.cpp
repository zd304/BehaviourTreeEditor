#include "NodeInfoParallel.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoParallel::NodeInfoParallel()
	: NodeInfo(NodeType::Parallel),
	mAbortType(AbortType::None)
{
	mAbortTxt = u8"无\0自打断\0打断低优先级";
}

void NodeInfoParallel::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSequence");
	FormUtility::FormCombo(u8"打断类型", (int*)&mAbortType, mAbortTxt);
	FormUtility::FormEnd();
}
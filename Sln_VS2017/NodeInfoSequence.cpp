#include "NodeInfoSequence.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSequence::NodeInfoSequence()
	: NodeInfo(NodeType::Sequence),
	mAbortType(AbortType::None)
{
	mAbortTxt = u8"无\0自打断\0打断低优先级";
}

void NodeInfoSequence::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSequence");
	FormUtility::FormCombo(u8"打断类型", (int*)&mAbortType, mAbortTxt);
	FormUtility::FormEnd();
}
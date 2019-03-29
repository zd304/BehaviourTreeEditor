#include "NodeInfoSelector.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSelector::NodeInfoSelector()
	: NodeInfo(NodeType::Selector),
	mAbortType(AbortType::None)
{
	mAbortTxt = u8"无\0自打断\0打断低优先级";
}

void NodeInfoSelector::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoSelector");
	FormUtility::FormCombo(u8"打断类型", (int*)&mAbortType, mAbortTxt);
	FormUtility::FormEnd();
}
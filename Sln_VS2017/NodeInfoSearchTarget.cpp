#include "NodeInfoSearchTarget.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoSearchTarget::NodeInfoSearchTarget()
	: NodeInfo(NodeType::SearchTarget)
{

}

void NodeInfoSearchTarget::OnGUI()
{
	NodeInfo::OnGUI();

	const char* searchTargetType = u8"被动\0主动搜寻敌对\0主动搜寻友方";
	const char* searchTargetCondition = u8"最近\0最远\0最高仇恨\0最低仇恨\0生命值小于\0生命值大于\0随机";

	FormUtility::FormBegin("##NodeInfoSearchTarget");
	FormUtility::FormCombo(u8"搜寻类型", (int*)&mSearchTargetType, searchTargetType);
	FormUtility::FormCombo(u8"搜寻条件", (int*)&mSearchTargetCondition, searchTargetCondition);
	mSearchDist.OnInspectorGUI(u8"搜寻范围", NULL);
	FormUtility::FormEnd();
}
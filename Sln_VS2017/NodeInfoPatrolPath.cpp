#include "NodeInfoPatrolPath.h"
#include "EDNode.h"
#include "FormUtility.h"

namespace ed = ax::NodeEditor;

NodeInfoPatrolPath::NodeInfoPatrolPath()
	: NodeInfo(NodeType::PatrolPath), patrolType(PatrolPathType::Once)
{

}

void NodeInfoPatrolPath::OnGUI()
{
	NodeInfo::OnGUI();

	FormUtility::FormBegin("##NodeInfoPatrolPath");
	const char* comboTxt = u8"单次\0乒乓\0循环";
	FormUtility::FormCombo(u8"巡逻方式", (int*)&patrolType, comboTxt);
	pathName.OnInspectorGUI(u8"巡逻路线名", NULL);
	FormUtility::FormEnd();
}
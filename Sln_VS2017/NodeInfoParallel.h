#pragma once

#include "NodeInfo.h"

enum BTPolicy
{
	RequireOne, // 一个成功/失败
	RequireAll, // 全部成功/失败
};

class NodeInfoParallel : public NodeInfo
{
public:
	NodeInfoParallel();

	void OnGUI();
public:
	BTPolicy mSuccessPolicy;
	BTPolicy mFailurePolicy;
};
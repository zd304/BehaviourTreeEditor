#pragma once

#include "NodeInfo.h"

class NodeInfoParallel : public NodeInfo
{
public:
	NodeInfoParallel();

	void OnGUI();
public:
	AbortType mAbortType;
private:
	const char* mAbortTxt;
};
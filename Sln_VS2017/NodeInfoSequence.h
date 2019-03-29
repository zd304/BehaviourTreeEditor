#pragma once

#include "NodeInfo.h"

class NodeInfoSequence : public NodeInfo
{
public:
	NodeInfoSequence();

	void OnGUI();
public:
	AbortType mAbortType;
private:
	const char* mAbortTxt;
};
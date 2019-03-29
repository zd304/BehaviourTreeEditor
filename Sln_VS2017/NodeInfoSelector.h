#pragma once

#include "NodeInfo.h"

class NodeInfoSelector : public NodeInfo
{
public:
	NodeInfoSelector();

	void OnGUI();
public:
	AbortType mAbortType;
private:
	const char* mAbortTxt;
};
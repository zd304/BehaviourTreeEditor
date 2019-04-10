#pragma once

#include "NodeInfoEntry.h"
#include "NodeInfoSelector.h"
#include "NodeInfoActiveSelector.h"
#include "NodeInfoSequence.h"
#include "NodeInfoParallel.h"

#include "NodeInfoPatrolRange.h"
#include "NodeInfoPatrolPath.h"
#include "NodeInfoSearchTarget.h"

class EDNode;

void SetCreateParentNodeFunc(CreateNodeFunc func);
void SetCreateLeafNodeFunc(CreateNodeFunc func);
void SetCreateRootNodeFunc(CreateNodeFunc func);

EDNode* CreateNode(NodeType nodeType, const char* name);
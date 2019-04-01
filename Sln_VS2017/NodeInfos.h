#pragma once

#include "NodeInfoEntry.h"
#include "NodeInfoSelector.h"
#include "NodeInfoSequence.h"
#include "NodeInfoParallel.h"

#include "NodeInfoPatrolRange.h"
#include "NodeInfoPatrolPath.h"
#include "NodeInfoSearchTarget.h"

class EDNode;

typedef EDNode* (*CreateNodeFunc)(const char* name);

void SetCreateParentNodeFunc(CreateNodeFunc func);
void SetCreateChildNodeFunc(CreateNodeFunc func);
EDNode* CreateNode(NodeType nodeType, const char* name);
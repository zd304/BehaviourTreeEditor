#pragma once

#include "NodeInfoEntry.h"
#include "NodeInfoSelector.h"
#include "NodeInfoActiveSelector.h"
#include "NodeInfoSequence.h"
#include "NodeInfoParallel.h"
#include "NodeInfoRandomSelector.h"
#include "NodeInfoRandomSequence.h"
#include "NodeInfoWeightRandomSelector.h"
#include "NodeInfoWeightRandomSequence.h"

#include "NodeInfoRepeat.h"

#include "NodeInfoHaveTarget.h"
#include "NodeInfoIsUsingSkill.h"

#include "NodeInfoPatrolRange.h"
#include "NodeInfoPatrolPath.h"
#include "NodeInfoSearchTarget.h"
#include "NodeInfoCastSkill.h"
#include "NodeInfoWait.h"
#include "NodeInfoSavePosition.h"

class EDNode;

void SetCreateParentNodeFunc(CreateNodeFunc func);
void SetCreateLeafNodeFunc(CreateNodeFunc func);
void SetCreateRootNodeFunc(CreateNodeFunc func);

EDNode* CreateNode(NodeType nodeType, const char* name);
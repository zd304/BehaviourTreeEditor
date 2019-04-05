#pragma once

#include "Application.h"
#include "NodeInfos.h"
#include "NodeEditor.h"
#include "Variables.h"
#include <vector>

class EDNode;
typedef EDNode* (*FindNodeFunc)(ax::NodeEditor::NodeId nodeID);

void SetNodeFindFunc(FindNodeFunc func);

EDNode* CreateNode(NodeType nodeType);
Variable* CreateVariable(VariableType varType);

void OnInspector();
void OnVarialbleGUI(std::vector<Variable*>& vars);
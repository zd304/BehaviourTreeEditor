#pragma once

#include "Application.h"
#include "NodeEditor.h"
#include "Variables.h"
#include <vector>

class EDNode;
typedef EDNode* (*FindNodeFunc)(ax::NodeEditor::NodeId nodeID);
typedef EDNode* (*CreateNodeFunc)(const char* name);

void SetNodeFindFunc(FindNodeFunc func);
void SetCreateParentNodeFunc(CreateNodeFunc func);
void SetCreateChildNodeFunc(CreateNodeFunc func);

EDNode* CreateNode(NodeType nodeType);

void OnInspector();
void OnVarialbleGUI(std::vector<Variable*>& vars);
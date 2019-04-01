# include "Application.h"
# include "NodeEditor.h"
# define IMGUI_DEFINE_MATH_OPERATORS
# include "imgui_internal.h"
#include <algorithm>
#include "EDNode.h"
#include "EDLink.h"
#include "NodeGUI.h"
#include "NodeInfos.h"
#include "Variables.h"

namespace ed = ax::NodeEditor;

static ed::EditorContext* g_Context = nullptr;
static std::vector<EDNode*>	g_Nodes;
static std::vector<EDLink*>	g_Links;
std::vector<Variable*> g_Variables;
static float HeightDiff = 120.0f;
static EDNode* EnterNode = NULL;

static int s_NextId = 10000;
static int GetNextId()
{
	return s_NextId++;
}

static int s_NextLinkID = 20000;
static int GetNextLinkId()
{
	return s_NextLinkID++;
}

static int s_NexNodeID = 30000;
static int GetNextNodeId()
{
	return s_NexNodeID++;
}

static int s_NexPinID = 40000;
static int GetNextPinId()
{
	return s_NexPinID++;
}

static EDNode* CreateParentNode(const char* name)
{
	EDNode* node = new EDNode(GetNextNodeId(), name);
	g_Nodes.push_back(node);

	node->inputPin.emplace_back(GetNextPinId(), "input");
	node->outputPin.emplace_back(GetNextPinId(), "output");

	BuildNode(node);
	return node;
}

static EDNode* CreateChildNode(const char* name)
{
	EDNode* node = new EDNode(GetNextNodeId(), name);
	g_Nodes.push_back(node);

	node->inputPin.emplace_back(GetNextPinId(), "input");

	BuildNode(node);
	return node;
}

static void ClearGraph()
{
	for (size_t i = 0; i < g_Nodes.size(); ++i)
	{
		EDNode* node = g_Nodes[i];
		if (node)
		{
			delete node;
		}
	}
	g_Nodes.clear();
	for (size_t i = 0; i < g_Links.size(); ++i)
	{
		EDLink* link = g_Links[i];
		if (link)
		{
			delete link;
		}
	}
	g_Links.clear();
}

static inline ImRect ImGui_GetItemRect()
{
	return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
}

static EDPin* FindPin(ed::PinId id)
{
	if (!id)
		return nullptr;

	for (size_t i = 0; i < g_Nodes.size(); ++i)
	{
		EDNode* node = g_Nodes[i];

		for (size_t i = 0; i < node->inputPin.size(); ++i)
		{
			EDPin* pin = &node->inputPin[i];
			if (pin->id == id)
				return pin;
		}
		
		for (size_t i = 0; i < node->outputPin.size(); ++i)
		{
			EDPin* pin = &node->outputPin[i];
			if (pin->id == id)
				return pin;
		}
	}

	return nullptr;
}

static EDLink* FindLink(ed::LinkId linkID)
{
	for (size_t i = 0; i < g_Links.size(); ++i)
	{
		EDLink* link = g_Links[i];
		if (!link) continue;
		if (link->id == linkID)
			return link;
	}
	return NULL;
}

static EDNode* FindNode(ed::NodeId nodeID)
{
	for (size_t i = 0; i < g_Nodes.size(); ++i)
	{
		EDNode* node = g_Nodes[i];
		if (!node) continue;
		if (node->id == nodeID)
			return node;
	}
	return NULL;
}

static void MakeLink(ed::PinId startPinID, ed::PinId endPinID)
{
	EDPin* startPin = FindPin(startPinID);
	EDPin* endPin = FindPin(endPinID);
	EDNode* startNode = NULL;
	EDNode* endNode = NULL;
	if (startPin)
	{
		if (startPin->kind != PinKind::Output)
		{
			return;
		}
		startNode = startPin->node;
	}
	if (endPin)
	{
		if (endPin->kind != PinKind::Input)
		{
			return;
		}
		endNode = endPin->node;
	}
	if (!startNode || !endNode)
		return;
	if (endNode->parent == startNode)
		return;
	if (startNode->maxOutput <= startNode->curOutput)
	{
		return;
	}
	endNode->parent = startNode;
	startNode->children.push_back(endNode);

	EDLink* link = new EDLink(GetNextLinkId(), startPinID, endPinID);
	g_Links.push_back(link);
	++startNode->curOutput;
}

static void DelLink(ed::LinkId linkID)
{
	EDLink* link = FindLink(linkID);
	if (!link) return;
	EDPin* startPin = FindPin(link->startPinId);
	EDPin* endPin = FindPin(link->endPinId);
	EDNode* startNode = NULL;
	EDNode* endNode = NULL;
	if (startPin)
	{
		startNode = startPin->node;
	}
	if (endPin)
	{
		endNode = endPin->node;
	}
	if (!startNode || !endNode)
		return;
	for (std::vector<EDNode*>::iterator it = startNode->children.begin();
		it != startNode->children.end(); ++it)
	{
		EDNode* child = *it;
		if (!child || child != endNode) continue;
		startNode->children.erase(it);
		break;
	}
	endNode->parent = NULL;

	auto id = std::find_if(g_Links.begin(), g_Links.end(), [linkID](auto& link) { return link->id == linkID; });
	if (id != g_Links.end())
		g_Links.erase(id);
	--startNode->curOutput;
}

void Application_Initialize()
{
	InitNodeTypeNames();
	SetNodeFindFunc(FindNode);
	SetCreateParentNodeFunc(CreateParentNode);
	SetCreateChildNodeFunc(CreateChildNode);

	g_Variables.clear();
	s_NextId = 1;

    ed::Config config;
    config.SettingsFile = "Simple.json";
    g_Context = ed::CreateEditor(&config);

	EnterNode = new EDNode(GetNextNodeId(), u8"开始");
	g_Nodes.push_back(EnterNode);

	EnterNode->outputPin.emplace_back(GetNextPinId(), "output");
	EnterNode->maxOutput = 1;
	EnterNode->nodeInfo = new NodeInfoEntry();

	BuildNode(EnterNode);
}

void Application_Finalize()
{
	ClearGraph();
    ed::DestroyEditor(g_Context);
}

void LeftView()
{
	//ImGui::Scrollbar(ImGuiLayoutType_Horizontal);
	
	ImGui::BeginTabBar("ViewTabs");
	if (ImGui::BeginTabItem(u8"总览"))
	{
		ImGui::EndTabItem();
	}
	
	if (ImGui::BeginTabItem(u8"检视"))
	{
		OnInspector();
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem(u8"变量"))
	{
		OnVarialbleGUI(g_Variables);
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem(u8"行为"))
	{
		ImGui::Text("This is Create Behavior tab");
		ImGui::EndTabItem();
	}
	
	ImGui::EndTabBar();

	//ImGui::Scrollbar(ImGuiLayoutType_Vertical);
}

void Application_Frame()
{
	s_NextId = 1000;
	static EDPin* newLinkPin = nullptr;
	static EDPin* newNodeLinkPin = nullptr;

    auto& io = ImGui::GetIO();

    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ImGui::Separator();

    ed::SetCurrentEditor(g_Context);

	ImGui::BeginChild("##Selection", ImVec2(300.0f, 0));
	LeftView();
	ImGui::EndChild();
	ImGui::SameLine();

    ed::Begin("My Editor", ImVec2(0.0, 0.0f));

	for (size_t i = 0; i < g_Nodes.size(); ++i)
	{
		EDNode* node = g_Nodes[i];

		if (node->parent == NULL)
		{
			ResetNodeTreePos(node, HeightDiff);
		}

		const float rounding = 5.0f;
		const float padding = 12.0f;

		const auto pinBackground = ed::GetStyle().Colors[ed::StyleColor_NodeBg];

		ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(128, 128, 128, 200));
		ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
		ed::PushStyleColor(ed::StyleColor_PinRect, ImColor(60, 180, 255, 150));
		ed::PushStyleColor(ed::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

		ed::PushStyleVar(ed::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
		ed::PushStyleVar(ed::StyleVar_NodeRounding, rounding);
		ed::PushStyleVar(ed::StyleVar_SourceDirection, ImVec2(0.0f, 1.0f));
		ed::PushStyleVar(ed::StyleVar_TargetDirection, ImVec2(0.0f, -1.0f));
		ed::PushStyleVar(ed::StyleVar_LinkStrength, 0.0f);
		ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 1.0f);
		ed::PushStyleVar(ed::StyleVar_PinRadius, 5.0f);
		ed::BeginNode(node->id);

		ImGui::BeginVertical(node->id.AsPointer());

		ImRect inputsRect;
		ImRect outputsRect;
		ImRect contentRect;
		int inputAlpha = 200;
		int outputAlpha = 200;
		// 画Node;
		{
			// 画Input;
			if (!node->inputPin.empty())
			{
				ImGui::BeginHorizontal("inputs");
				ImGui::Spring(0, padding * 2);

				EDPin* pin = &node->inputPin[0];
				ImGui::Dummy(ImVec2(0, padding));
				ImGui::Spring(1, 0);
				inputsRect = ImGui_GetItemRect();
				ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
				ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
				ed::PushStyleVar(ed::StyleVar_PinCorners, 12);
				ed::BeginPin(pin->id, ed::PinKind::Input);
				ed::PinPivotRect(inputsRect.GetTL(), inputsRect.GetBR());
				ed::PinRect(inputsRect.GetTL(), inputsRect.GetBR());
				ed::EndPin();
				ed::PopStyleVar(3);

				ImGui::Spring(0, padding * 2);
				ImGui::EndHorizontal();
			}
			else
			{
				ImGui::Dummy(ImVec2(0, padding));
			}

			// 画内容;
			{
				ImGui::BeginHorizontal("content_frame");
				ImGui::Spring(1, padding);

				ImGui::BeginVertical("content", ImVec2(0.0f, 0.0f));
				ImGui::Dummy(ImVec2(160, 0));
				ImGui::Spring(1);
				ImGui::TextUnformatted(node->name.c_str());
				ImGui::Spring(1);
				ImGui::EndVertical();
				contentRect = ImGui_GetItemRect();

				ImGui::Spring(1, padding);
				ImGui::EndHorizontal();
			}

			// 画Output;
			if (!node->outputPin.empty())
			{
				ImGui::BeginHorizontal("outputs");
				ImGui::Spring(0, padding * 2);

				EDPin* pin = &node->outputPin[0];
				ImGui::Dummy(ImVec2(0, padding));
				ImGui::Spring(1, 0);
				outputsRect = ImGui_GetItemRect();
				ed::PushStyleVar(ed::StyleVar_PinCorners, 3);
				ed::BeginPin(pin->id, ed::PinKind::Output);
				ed::PinPivotRect(outputsRect.GetTL(), outputsRect.GetBR());
				ed::PinRect(outputsRect.GetTL(), outputsRect.GetBR());
				ed::EndPin();
				ed::PopStyleVar();

				ImGui::Spring(0, padding * 2);
				ImGui::EndHorizontal();
			}
			else
			{
				ImGui::Dummy(ImVec2(0, padding));
			}
		}

		ImGui::EndVertical();

		ed::EndNode();
		ed::PopStyleVar(7);
		ed::PopStyleColor(4);

		// 画Pin;
		auto drawList = ed::GetNodeBackgroundDrawList(node->id);

		drawList->AddRectFilled(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
			IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), inputAlpha), 4.0f, 12);
		//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
		drawList->AddRect(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
			IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), inputAlpha), 4.0f, 12);
		//ImGui::PopStyleVar();
		drawList->AddRectFilled(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
			IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), outputAlpha), 4.0f, 3);
		//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
		drawList->AddRect(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
			IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), outputAlpha), 4.0f, 3);
		//ImGui::PopStyleVar();
		drawList->AddRectFilled(contentRect.GetTL(), contentRect.GetBR(), IM_COL32(24, 64, 128, 200), 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
		drawList->AddRect(
			contentRect.GetTL(),
			contentRect.GetBR(),
			IM_COL32(48, 128, 255, 100), 0.0f);
		//ImGui::PopStyleVar();
	}

	for (size_t i = 0; i < g_Links.size(); ++i)
	{
		EDLink* link = g_Links[i];
		ed::Link(link->id, link->startPinId, link->endPinId);
	}

	// 创建两个Node之间的连线;
	if (ed::BeginCreate(ImColor(255, 255, 255), 2.0f))
	{
		ed::PinId startPinId = 0, endPinId = 0;
		if (ed::QueryNewLink(&startPinId, &endPinId))
		{
			auto startPin = FindPin(startPinId);
			auto endPin = FindPin(endPinId);

			newLinkPin = startPin ? startPin : endPin;

			if (startPin->kind == PinKind::Input)
			{
				std::swap(startPin, endPin);
				std::swap(startPinId, endPinId);
			}

			if (startPin && endPin)
			{
				if (endPin == startPin)
				{
					ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
				}
				else if (endPin->kind == startPin->kind)
				{
					ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
				}
				else
				{
					if (ed::AcceptNewItem(ImColor(128, 255, 128), 4.0f))
					{
						MakeLink(startPinId, endPinId);
					}
				}
			}
		}

		// 放开鼠标时候没有连接别的Pin;
		ed::PinId pinId = 0;
		if (ed::QueryNewNode(&pinId))
		{
			newLinkPin = FindPin(pinId);

			if (ed::AcceptNewItem())
			{
				// createNewNode = true;
				newNodeLinkPin = FindPin(pinId);
				newLinkPin = nullptr;
				ed::Suspend();
				ImGui::OpenPopup("Create New Node");
				ed::Resume();
			}
		}
	}
	else
	{
		newLinkPin = NULL;
	}
	ed::EndCreate();

	// 删除两个Node之间的连线;
	if (ed::BeginDelete())
	{
		ed::LinkId linkId = 0;
		while (ed::QueryDeletedLink(&linkId))
		{
			if (ed::AcceptDeletedItem())
			{
				DelLink(linkId);
			}
		}

		ed::NodeId nodeId = 0;
		while (ed::QueryDeletedNode(&nodeId))
		{
			if (ed::AcceptDeletedItem())
			{
				auto id = std::find_if(g_Nodes.begin(), g_Nodes.end(), [nodeId](auto& node) { return node->id == nodeId; });
				if (id != g_Nodes.end())
					g_Nodes.erase(id);
			}
		}
	}
	ed::EndDelete();

	ImVec2 openPopupPosition = ImGui::GetMousePos();
	ed::Suspend();
	if (ed::ShowBackgroundContextMenu())
	{
		ImGui::OpenPopup("Create New Node");
		newNodeLinkPin = nullptr;
	}
	ed::Resume();

	// 创建新的Node;
	ed::Suspend();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
	if (ImGui::BeginPopup("Create New Node"))
	{
		ImVec2 newNodePostion = openPopupPosition;

		EDNode* node = nullptr;

		if (ImGui::BeginMenu(u8"复合节点"))
		{
			for (auto it = nodeTypeNames.begin();
				it != nodeTypeNames.end(); ++it)
			{
				if ((int)it->first < 1 || (int)it->first > 100)
					continue;
				std::string txt = u8"创建[" + it->second + u8"]";
			
				if (ImGui::MenuItem(txt.c_str()))
					node = CreateNode(it->first);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"装饰节点"))
		{
			for (auto it = nodeTypeNames.begin();
				it != nodeTypeNames.end(); ++it)
			{
				if ((int)it->first < 101 || (int)it->first > 1000)
					continue;
				std::string txt = u8"创建[" + it->second + u8"]";

				if (ImGui::MenuItem(txt.c_str()))
					node = CreateNode(it->first);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"条件节点"))
		{
			for (auto it = nodeTypeNames.begin();
				it != nodeTypeNames.end(); ++it)
			{
				if ((int)it->first < 1001 || (int)it->first > 2000)
					continue;
				std::string txt = u8"创建[" + it->second + u8"]";

				if (ImGui::MenuItem(txt.c_str()))
					node = CreateNode(it->first);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"行为节点"))
		{
			for (auto it = nodeTypeNames.begin();
				it != nodeTypeNames.end(); ++it)
			{
				if ((int)it->first < 2001)
					continue;
				std::string txt = u8"创建[" + it->second + u8"]";

				if (ImGui::MenuItem(txt.c_str()))
					node = CreateNode(it->first);
			}
			ImGui::EndMenu();
		}

		if (node)
		{
			ed::SetNodePosition(node->id, newNodePostion);

			if (EDPin* startPin = newNodeLinkPin)
			{
				std::vector<EDPin>* pins = startPin->kind == PinKind::Input ? &node->outputPin : &node->inputPin;

				for (size_t i = 0; i < pins->size(); ++i)
				{
					EDPin* pin = &(*pins)[i];
					if (pin && CanCreateLink(startPin, pin))
					{
						EDPin* endPin = pin;
						if (startPin->kind == PinKind::Input)
							std::swap(startPin, endPin);

						MakeLink(startPin->id, endPin->id);

						break;
					}
				}
			}
		}

		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();
	ed::Resume();

    ed::End();
    ed::SetCurrentEditor(nullptr);
}


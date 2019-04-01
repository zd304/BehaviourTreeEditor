#pragma once
#include <string>
#include <map>
#include "imgui.h"

enum NodeType
{
	Entry = 0,

	Selector = 1,
	Sequence,
	Parallel,
	RandomSelector,
	RandomSequence,

	Repeat = 101,
	Success,
	Inverter,

	MoveTo = 2001,
	PatrolRange,
	PatrolPath,
	SearchTarget,
};

enum AbortType
{
	None,
	Self,
	LowPriority
};

extern std::map<NodeType, std::string> nodeTypeNames;

std::string UTS(const std::string& str);
std::string STU(const std::string& str);

#define SAFE_DELETE(x) if (x) { delete x; x = NULL; }
#define SAFE_DELETE_ARRAY(x) if (x) { delete [] x; x = NULL; }
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }

ImTextureID Application_LoadTexture(const char* path);
ImTextureID Application_CreateTexture(const void* data, int width, int height);
void        Application_DestroyTexture(ImTextureID texture);
int         Application_GetTextureWidth(ImTextureID texture);
int         Application_GetTextureHeight(ImTextureID texture);

void InitNodeTypeNames();
void Application_Initialize();
void Application_Finalize();
void Application_Frame();

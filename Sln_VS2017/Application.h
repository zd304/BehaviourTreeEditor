#pragma once
#include <string>
#include <map>
#include "imgui.h"

static float leftViewWidth = 320.0f;

std::string UTS(const std::string& str);
std::string STU(const std::string& str);
void StringReplace(std::string &strBase, const std::string& strSrc, const std::string& strDes);

#define SAFE_DELETE(x) if (x) { delete x; x = NULL; }
#define SAFE_DELETE_ARRAY(x) if (x) { delete [] x; x = NULL; }
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }

ImTextureID Application_LoadTexture(const char* path);
ImTextureID Application_CreateTexture(const void* data, int width, int height);
void        Application_DestroyTexture(ImTextureID texture);
int         Application_GetTextureWidth(ImTextureID texture);
int         Application_GetTextureHeight(ImTextureID texture);

void Application_Initialize();
void Application_Finalize();
void Application_Frame();

class Global
{
public:
	static ImTextureID mFolderTexID;
	static ImTextureID mFileTexID;
	static ImTextureID mDiskTexID;
};

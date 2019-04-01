#include "Application.h"
#include <Windows.h>

std::map<NodeType, std::string> nodeTypeNames;

void InitNodeTypeNames()
{
	nodeTypeNames[NodeType::Entry] = u8"开始";

	nodeTypeNames[NodeType::Selector] = u8"选择节点";
	nodeTypeNames[NodeType::Sequence] = u8"顺序节点";
	nodeTypeNames[NodeType::Parallel] = u8"并行节点";
	nodeTypeNames[NodeType::RandomSelector] = u8"随机选择节点";
	nodeTypeNames[NodeType::RandomSequence] = u8"随机顺序节点";

	nodeTypeNames[NodeType::Repeat] = u8"重复节点";
	nodeTypeNames[NodeType::Success] = u8"成功节点";
	nodeTypeNames[NodeType::Inverter] = u8"逆变节点";

	nodeTypeNames[NodeType::PatrolRange] = u8"范围巡逻";
}

std::string UTS(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

std::string STU(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
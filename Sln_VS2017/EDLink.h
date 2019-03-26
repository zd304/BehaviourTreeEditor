#pragma once

#include "EDPin.h"

struct EDLink
{
	ed::LinkId id;

	ed::PinId startPinId;
	ed::PinId endPinId;

	EDLink(int linkID, ed::PinId startPinID, ed::PinId endPinID)
		: id(linkID), startPinId(startPinID), endPinId(endPinID)
	{

	}
};
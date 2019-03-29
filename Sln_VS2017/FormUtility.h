#pragma once

#include <stdlib.h>

namespace FormUtility
{
	void FormBegin(const char* spr_id, float offset = 120.0f);

	void FormLabelText(const char* label, const char* text);

	void FormVector3(const char* label, float x, float y, float z);

	bool FormInt(const char* label, int* v, const char* btnName = NULL);

	bool FormCheckBox(const char* label, bool* check);

	bool FormCombo(const char* label, int* current_item, const char* items_seperated_by_zeros, int pop_max_height_in_items = -1);

	void FormEnd();
};
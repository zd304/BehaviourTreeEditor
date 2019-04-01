#pragma once

#include <stdlib.h>

namespace FormUtility
{
	void FormBegin(const char* spr_id, float offset = 120.0f);

	void FormLabelText(const char* label, const char* text);

	bool FormInt(const char* label, int* v, const char* btnName = NULL);

	bool FormFloat(const char* label, float* v, const char* btnName = NULL);

	bool FormBool(const char* label, bool* v, const char* btnName = NULL);

	bool FormString(const char* label, char* v, size_t size, const char* btnName = NULL);

	bool FormVector2(const char* label, float& x, float& y, const char* btnName = NULL);

	bool FormVector3(const char* label, float& x, float& y, float& z, const char* btnName = NULL);

	bool FormVector4(const char* label, float& x, float& y, float& z, float& w, const char* btnName = NULL);

	bool FormCheckBox(const char* label, bool* check);

	bool FormComboButton(const char* label, int* current_item, const char* items_seperated_by_zeros, int pop_max_height_in_items = -1, const char* btnName = NULL);

	bool FormCombo(const char* label, int* current_item, const char* items_seperated_by_zeros, int pop_max_height_in_items = -1);

	bool FormInputText(const char* label, char* buf, size_t size);

	void FormEnd();
};
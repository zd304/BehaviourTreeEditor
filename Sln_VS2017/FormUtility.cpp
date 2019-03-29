#include "FormUtility.h"
#include "imgui.h"
#include <iostream>

namespace FormUtility
{
	void FormBegin(const char* spr_id, float offset)
	{
		ImGui::Columns(2, spr_id, false);
		ImGui::SetColumnOffset(1, offset);
	}

	void FormLabelText(const char* label, const char* text)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::Text(text);
		ImGui::NextColumn();
	}

	void FormVector3(const char* label, float x, float y, float z)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		float v[3] = {
			x, y, z
		};
		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FV%s", label);
		ImGui::PushID(c);
		ImGui::InputFloat3("", v);
		ImGui::PopID();
		ImGui::NextColumn();
	}

	bool FormInt(const char* label, int* v, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FINT%s", label);
		ImGui::PushID(c);
		ImGui::DragInt("", v);
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			rst = ImGui::Button(btnName);
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormCheckBox(const char* label, bool* check)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FCB%s", label);
		ImGui::PushID(c);
		bool rst = ImGui::Checkbox("", check);
		ImGui::PopID();
		ImGui::NextColumn();
		return rst;
	}

	bool FormCombo(const char* label, int* current_item, const char* items_seperated_by_zeros, int pop_max_height_in_items)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FCB%s", label);
		ImGui::PushID(c);
		bool rst = ImGui::Combo("", current_item, items_seperated_by_zeros, pop_max_height_in_items);
		ImGui::PopID();
		ImGui::NextColumn();
		return rst;
	}

	void FormEnd()
	{
		ImGui::Columns();
	}
};
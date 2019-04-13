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

	void FormTextMultiline(const char* label, char* buf, size_t bufSize, ImVec2 size)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FMULTITXT%s", label);

		ImGui::PushID(c);
		ImGui::InputTextMultiline("", buf, bufSize, size);
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
			sprintf_s(c, "#FBTNINT%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormFloat(const char* label, float* v, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FFLOAT%s", label);
		ImGui::PushID(c);
		ImGui::DragFloat("", v);
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNFLOAT%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormBool(const char* label, bool* v, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FBOOL%s", label);
		ImGui::PushID(c);
		ImGui::Checkbox("", v);
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNBOOL%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormString(const char* label, char* v, size_t size, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FSTRING%s", label);
		ImGui::PushID(c);
		ImGui::InputText("", v, size);
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNSTR%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormVector2(const char* label, float& x, float& y, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FV2%s", label);
		ImGui::PushID(c);
		float v[2] = {
			x, y
		};
		ImGui::DragFloat2("", v);
		x = v[0];
		y = v[1];
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNV2%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormVector3(const char* label, float& x, float& y, float& z, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FV3%s", label);
		ImGui::PushID(c);
		float v[3] = {
			x, y, z
		};
		ImGui::DragFloat3("", v);
		x = v[0];
		y = v[1];
		z = v[2];
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNV3%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormVector4(const char* label, float& x, float& y, float& z, float& w, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FV4%s", label);
		ImGui::PushID(c);
		float v[4] = {
			x, y, z, w
		};
		ImGui::DragFloat4("", v);
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNV4%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
		}
		ImGui::NextColumn();

		return rst;
	}

	bool FormComboButton(const char* label, int* current_item, const char* items_seperated_by_zeros, int pop_max_height_in_items, const char* btnName)
	{
		bool rst = true;

		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FCOMBOBTN%s", label);
		ImGui::PushID(c);
		rst = ImGui::Combo("", current_item, items_seperated_by_zeros, pop_max_height_in_items);
		ImGui::PopID();

		if (btnName != NULL)
		{
			ImGui::SameLine();
			sprintf_s(c, "#FBTNCOM%s", label);
			ImGui::PushID(c);
			rst = ImGui::Button(btnName);
			ImGui::PopID();
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

	bool FormInputText(const char* label, char* buf, size_t size)
	{
		ImGui::Text(label);
		ImGui::NextColumn();

		char c[128];
		memset(c, 0, 128);
		sprintf_s(c, "#FCB%s", label);
		ImGui::PushID(c);
		bool rst = ImGui::InputText("", buf, size);
		ImGui::PopID();
		ImGui::NextColumn();
		return rst;
	}

	void FormEnd()
	{
		ImGui::Columns();
	}
};
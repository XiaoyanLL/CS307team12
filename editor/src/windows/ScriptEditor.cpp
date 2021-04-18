#include "windows/ScriptEditor.h"

void ScriptEditor::draw()
{
    // Script editor
    if (visible)
    {
        // set the windows default size
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);

        static char script_name[128] = "";
        bool script_info = false;
        if (ImGui::Begin("Script Editor", &visible))
        {
            ImGui::PushItemWidth(200);
            ImGui::InputText("##script_name", script_name, IM_ARRAYSIZE(script_name));
            if (ImGui::Button("Create Script"))
            {
                editor->getGamePtr()->createScript(std::string(script_name));
            }
            if (ImGui::BeginListBox("", ImVec2(200, 8 * ImGui::GetTextLineHeightWithSpacing())))
            {
                std::vector<Core::Script> *t = nullptr;
                // Set default selected entity to be the first in the entity list
                if (editor->getCurrentComponentList()[CUR_SCRIPT] == "No Component Selected" && (t = editor->getGamePtr()->getScriptsList())->size() > 0)
                {
                    editor->getCurrentComponentList()[CUR_SCRIPT] = editor->getGamePtr()->getScriptsList()->at(0).getScriptName();
                }

                for (int i = 0; t && i < t->size(); i++)
                {
                    auto s = t->at(i);
                    bool is_selected = (currScriptId == i);
                    if (ImGui::Selectable(s.getScriptName().c_str(), is_selected))
                    {
                        currScriptId = i;
                        editor->getCurrentComponentList()[CUR_SCRIPT] = s.getScriptName().c_str();
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }
            //ImGui::SameLine();
            if (ImGui::Button("Delete Script"))
            {
            }
            if (ImGui::Button("Link Script"))
            {
            }
            ImGui::SameLine();
            if (ImGui::Button("Show Information"))
            {
                script_info = true;
            }
        }

        ImGui::End();
    }
}
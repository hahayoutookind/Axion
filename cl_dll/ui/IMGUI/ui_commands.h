#pragma once

#include "imgui_window.h"
#include "imgui_utils.h"
#include "imgui.h"

class CImGuiCommands : public IImGuiWindow
{
public:
    void Initialize();
    void VidInitialize();
    void Terminate();
    void Think();
    void Draw();
    bool Active();
    bool CursorRequired();
    bool HandleKey(bool keyDown, int keyNumber, const char *bindName);

private:
    static void CmdShowCommandsWindow();

    void DrawTabClient();
    void DrawTabHUD();
    void DrawTabVisuals();
    void DrawTabCrosshair();
    void DrawCrosshairPreview(float previewSz);

    bool SidebarButton(const char* pLabel, ImTextureID iconTex, bool isSelected, ImVec2 btnSize, float uiScale, float xPos);

    static void HelpTooltip(const char* pCvarName, const char* pDesc, const char* pDefault = nullptr, const char* pRange   = nullptr);

    void DrawCheckbox(const char* pLabel, const char* pCvar, const char* pDesc, const char* pDef = "0");

    void DrawSliderFloatWithReset(const char* pLabel, const char* pCvar, float minVal, float maxVal, float defaultVal, const char* pDesc, const char* pFmt = "%.1f");

    void DrawSliderIntWithReset(const char* pLabel, const char* pCvar, int minVal, int maxVal, int defaultVal, const char* pDesc);

private:
    static bool m_ShowCommands;
    static int m_ActiveTab;

    ImGuiImage m_AppIcon;
    ImGuiImage m_CLSettingsIcon;
    ImGuiImage m_CrosshairIcon;
    ImGuiImage m_DrawIcon;
    ImGuiImage m_SettingsIcon;
};

extern CImGuiCommands g_ImGuiCommands;
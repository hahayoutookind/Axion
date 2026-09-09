#pragma once

#include "imgui_window.h"
#include "imgui.h"
#include "imgui_utils.h"

#include <string>
#include <vector>
#include <unordered_map>

enum class MenuItemType
{
    BUTTON,
    CHECKBOX,
    TEXT,
    SEPARATOR,
    SUBMENU,
    CLOSE_MENU,
    SAME_LINE,
    TABBAR,
    TAB,
    SLIDER_INT,
    SLIDER_FLOAT,
    COLOR_CVAR,
    SPACE,
    CONDITION,
    IMAGE,
    IMAGE_BUTTON,
    CVAR_CHECK
};

enum class CompareOp
{
    EQ, NE, GT, GE, LT, LE
};

struct MenuItem
{
    MenuItemType m_Type = MenuItemType::TEXT;

    std::string m_Label;
    std::string m_Command;
    std::string m_CvarName;

    float m_MinValue = 0.0f;
    float m_MaxValue = 1.0f;
    int m_MinInt = 0;
    int m_MaxInt = 100;

    std::string m_ConditionCvar;
    float m_ConditionValue = 0.0f;
    CompareOp m_ConditionOp = CompareOp::EQ;

    std::string m_ImagePath;
    ImGuiImage m_Image = {};
    bool m_ImageLoaded = false;
    float m_ImageWidth  = 0.0f;
    float m_ImageHeight = 0.0f;

    std::vector<MenuItem> m_Children;
};

struct MenuWindow
{
    std::string m_Title;
    bool m_IsOpen = true;
    std::vector<MenuItem> m_Items;
};

struct MenuStyleVar
{
    ImGuiStyleVar m_Idx = static_cast<ImGuiStyleVar>(-1);
    ImVec2 m_Value = {};
    bool m_IsVec2 = false;
};

struct MenuStyleColor
{
    ImGuiCol m_Idx = static_cast<ImGuiCol>(-1);
    ImVec4 m_Color = {};
};

class CImGuiCustomMenu : public IImGuiWindow
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

    void ExecMenu_f();
    bool LoadFromCfg(const char* pFilename);

private:
    void DrawWindow(MenuWindow& win);
    void DrawItemsRecursive(std::vector<MenuItem>& items);

    void DrawButton(MenuItem& item);
    void DrawCheckbox(MenuItem& item);
    void DrawCloseMenu(MenuItem& item);
    void DrawSubmenu(MenuItem& item);
    void DrawTabBar(MenuItem& item);
    void DrawSliderInt(MenuItem& item);
    void DrawSliderFloat(MenuItem& item);
    void DrawColorCvar(MenuItem& item);
    void DrawCondition(MenuItem& item);
    void DrawImage(MenuItem& item);
    void DrawImageButton(MenuItem& item);
    void DrawCvarCheck(MenuItem& item);

    void SetupDefaultMenuStyle();

    static ImGuiStyleVar GetStyleVarIndex(const std::string& name);
    static ImGuiCol GetColorIndex(const std::string& name);

    void FreeImagesRecursive(std::vector<MenuItem>& items);
    void FreeAllImages();

private:
    static bool m_ShowCustomMenu;

    std::string m_DefaultTitle = "Custom Menu";

    std::vector<MenuWindow> m_Windows;
    std::vector<MenuStyleVar> m_StyleVars;
    std::vector<MenuStyleColor> m_StyleColors;

    static const std::unordered_map<std::string, ImGuiStyleVar> s_StyleVarMap;
    static const std::unordered_map<std::string, ImGuiCol> s_ColorMap;
};

extern CImGuiCustomMenu g_iCustomMenu;
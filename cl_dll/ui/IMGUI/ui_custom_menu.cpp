#include "ui_custom_menu.h"

#include "hud.h"
#include "keydefs.h"
#include "cl_util.h"
#include "imgui_viewport.h"

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>

CImGuiCustomMenu g_iCustomMenu;
bool CImGuiCustomMenu::m_ShowCustomMenu = false;

const std::unordered_map<std::string, ImGuiStyleVar>
CImGuiCustomMenu::s_StyleVarMap =
{
    {"Alpha",                        ImGuiStyleVar_Alpha},
    {"DisabledAlpha",                ImGuiStyleVar_DisabledAlpha},
    {"WindowRounding",               ImGuiStyleVar_WindowRounding},
    {"WindowBorderSize",             ImGuiStyleVar_WindowBorderSize},
    {"ChildRounding",                ImGuiStyleVar_ChildRounding},
    {"ChildBorderSize",              ImGuiStyleVar_ChildBorderSize},
    {"PopupRounding",                ImGuiStyleVar_PopupRounding},
    {"PopupBorderSize",              ImGuiStyleVar_PopupBorderSize},
    {"FrameRounding",                ImGuiStyleVar_FrameRounding},
    {"FrameBorderSize",              ImGuiStyleVar_FrameBorderSize},
    {"IndentSpacing",                ImGuiStyleVar_IndentSpacing},
    {"ScrollbarSize",                ImGuiStyleVar_ScrollbarSize},
    {"ScrollbarRounding",            ImGuiStyleVar_ScrollbarRounding},
    {"ScrollbarPadding",             ImGuiStyleVar_ScrollbarPadding},
    {"GrabMinSize",                  ImGuiStyleVar_GrabMinSize},
    {"GrabRounding",                 ImGuiStyleVar_GrabRounding},
    {"ImageBorderSize",              ImGuiStyleVar_ImageBorderSize},
    {"TabRounding",                  ImGuiStyleVar_TabRounding},
    {"TabBorderSize",                ImGuiStyleVar_TabBorderSize},
    {"TabMinWidthBase",              ImGuiStyleVar_TabMinWidthBase},
    {"TabMinWidthShrink",            ImGuiStyleVar_TabMinWidthShrink},
    {"TabBarBorderSize",             ImGuiStyleVar_TabBarBorderSize},
    {"TabBarOverlineSize",           ImGuiStyleVar_TabBarOverlineSize},
    {"TableAngledHeadersAngle",      ImGuiStyleVar_TableAngledHeadersAngle},
    {"TreeLinesSize",                ImGuiStyleVar_TreeLinesSize},
    {"TreeLinesRounding",            ImGuiStyleVar_TreeLinesRounding},
    {"SeparatorTextBorderSize",      ImGuiStyleVar_SeparatorTextBorderSize},
    {"WindowPadding",                ImGuiStyleVar_WindowPadding},
    {"WindowMinSize",                ImGuiStyleVar_WindowMinSize},
    {"WindowTitleAlign",             ImGuiStyleVar_WindowTitleAlign},
    {"FramePadding",                 ImGuiStyleVar_FramePadding},
    {"ItemSpacing",                  ImGuiStyleVar_ItemSpacing},
    {"ItemInnerSpacing",             ImGuiStyleVar_ItemInnerSpacing},
    {"CellPadding",                  ImGuiStyleVar_CellPadding},
    {"TableAngledHeadersTextAlign",  ImGuiStyleVar_TableAngledHeadersTextAlign},
    {"ButtonTextAlign",              ImGuiStyleVar_ButtonTextAlign},
    {"SelectableTextAlign",          ImGuiStyleVar_SelectableTextAlign},
    {"SeparatorTextAlign",           ImGuiStyleVar_SeparatorTextAlign},
    {"SeparatorTextPadding",         ImGuiStyleVar_SeparatorTextPadding},
};

const std::unordered_map<std::string, ImGuiCol>
CImGuiCustomMenu::s_ColorMap =
{
    {"Text",                         ImGuiCol_Text},
    {"TextDisabled",                 ImGuiCol_TextDisabled},
    {"WindowBg",                     ImGuiCol_WindowBg},
    {"ChildBg",                      ImGuiCol_ChildBg},
    {"PopupBg",                      ImGuiCol_PopupBg},
    {"Border",                       ImGuiCol_Border},
    {"BorderShadow",                 ImGuiCol_BorderShadow},
    {"FrameBg",                      ImGuiCol_FrameBg},
    {"FrameBgHovered",               ImGuiCol_FrameBgHovered},
    {"FrameBgActive",                ImGuiCol_FrameBgActive},
    {"TitleBg",                      ImGuiCol_TitleBg},
    {"TitleBgActive",                ImGuiCol_TitleBgActive},
    {"TitleBgCollapsed",             ImGuiCol_TitleBgCollapsed},
    {"MenuBarBg",                    ImGuiCol_MenuBarBg},
    {"ScrollbarBg",                  ImGuiCol_ScrollbarBg},
    {"ScrollbarGrab",                ImGuiCol_ScrollbarGrab},
    {"ScrollbarGrabHovered",         ImGuiCol_ScrollbarGrabHovered},
    {"ScrollbarGrabActive",          ImGuiCol_ScrollbarGrabActive},
    {"CheckMark",                    ImGuiCol_CheckMark},
    {"SliderGrab",                   ImGuiCol_SliderGrab},
    {"SliderGrabActive",             ImGuiCol_SliderGrabActive},
    {"Button",                       ImGuiCol_Button},
    {"ButtonHovered",                ImGuiCol_ButtonHovered},
    {"ButtonActive",                 ImGuiCol_ButtonActive},
    {"Header",                       ImGuiCol_Header},
    {"HeaderHovered",                ImGuiCol_HeaderHovered},
    {"HeaderActive",                 ImGuiCol_HeaderActive},
    {"Separator",                    ImGuiCol_Separator},
    {"SeparatorHovered",             ImGuiCol_SeparatorHovered},
    {"SeparatorActive",              ImGuiCol_SeparatorActive},
    {"ResizeGrip",                   ImGuiCol_ResizeGrip},
    {"ResizeGripHovered",            ImGuiCol_ResizeGripHovered},
    {"ResizeGripActive",             ImGuiCol_ResizeGripActive},
    {"InputTextCursor",              ImGuiCol_InputTextCursor},
    {"TabHovered",                   ImGuiCol_TabHovered},
    {"Tab",                          ImGuiCol_Tab},
    {"TabSelected",                  ImGuiCol_TabSelected},
    {"TabSelectedOverline",          ImGuiCol_TabSelectedOverline},
    {"TabDimmed",                    ImGuiCol_TabDimmed},
    {"TabDimmedSelected",            ImGuiCol_TabDimmedSelected},
    {"TabDimmedSelectedOverline",    ImGuiCol_TabDimmedSelectedOverline},
    {"PlotLines",                    ImGuiCol_PlotLines},
    {"PlotLinesHovered",             ImGuiCol_PlotLinesHovered},
    {"PlotHistogram",                ImGuiCol_PlotHistogram},
    {"PlotHistogramHovered",         ImGuiCol_PlotHistogramHovered},
    {"TableHeaderBg",                ImGuiCol_TableHeaderBg},
    {"TableBorderStrong",            ImGuiCol_TableBorderStrong},
    {"TableBorderLight",             ImGuiCol_TableBorderLight},
    {"TableRowBg",                   ImGuiCol_TableRowBg},
    {"TableRowBgAlt",                ImGuiCol_TableRowBgAlt},
    {"TextLink",                     ImGuiCol_TextLink},
    {"TextSelectedBg",               ImGuiCol_TextSelectedBg},
    {"TreeLines",                    ImGuiCol_TreeLines},
    {"DragDropTarget",               ImGuiCol_DragDropTarget},
    {"UnsavedMarker",                ImGuiCol_UnsavedMarker},
    {"NavCursor",                    ImGuiCol_NavCursor},
    {"NavWindowingHighlight",        ImGuiCol_NavWindowingHighlight},
    {"NavWindowingDimBg",            ImGuiCol_NavWindowingDimBg},
    {"ModalWindowDimBg",             ImGuiCol_ModalWindowDimBg},
};

namespace
{
    void TrimRight(char* pStr)
    {
        size_t len = std::strlen(pStr);
        while (len > 0 && (pStr[len-1] == '\n' || pStr[len-1] == '\r' || pStr[len-1] == ' '  || pStr[len-1] == '\t'))
            pStr[--len] = '\0';
    }

    void TrimLeft(std::string& str)
    {
        const size_t startPos = str.find_first_not_of(" \t");
        if (startPos == std::string::npos)
            str.clear();
        else if (startPos > 0)
            str.erase(0, startPos);
    }

    bool StartsWith(const std::string& str, const char* pPrefix)
    {
        const size_t prefixLen = std::strlen(pPrefix);
        return str.size() >= prefixLen && str.compare(0, prefixLen, pPrefix) == 0;
    }

    bool ExtractQuoted(const std::string& str, std::initializer_list<std::string*> outList)
    {
        size_t searchPos = 0;
        for (std::string* pDst : outList)
        {
            const size_t openPos  = str.find('"', searchPos);
            if (openPos == std::string::npos) 
                return false;
            const size_t closePos = str.find('"', openPos + 1);
            if (closePos == std::string::npos || closePos <= openPos) 
                return false;

            *pDst = str.substr(openPos + 1, closePos - openPos - 1);
            searchPos = closePos + 1;
        }
        return true;
    }
}

static void ExecMenuCmd_f()
{
    g_iCustomMenu.ExecMenu_f();
}

void CImGuiCustomMenu::Initialize()
{
    gEngfuncs.pfnAddCommand("exec_menu", ExecMenuCmd_f);
}

void CImGuiCustomMenu::VidInitialize() {}

void CImGuiCustomMenu::Terminate()
{
    FreeAllImages();
    m_Windows.clear();
    m_StyleVars.clear();
    m_StyleColors.clear();
}

void CImGuiCustomMenu::Think() {}

bool CImGuiCustomMenu::Active()
{
    return m_ShowCustomMenu;
}

bool CImGuiCustomMenu::CursorRequired()
{
    return m_ShowCustomMenu;
}

bool CImGuiCustomMenu::HandleKey(bool keyDown, int keyNumber, const char *bindName)
{
    if (keyNumber == K_ESCAPE && keyDown && m_ShowCustomMenu)
    {
        m_ShowCustomMenu = false;
        return true;
    }
    return false;
}

void CImGuiCustomMenu::Draw()
{
    if (!m_ShowCustomMenu)
        return;

    for (const auto& styleVar : m_StyleVars)
    {
        if (styleVar.m_Idx == static_cast<ImGuiStyleVar>(-1)) 
            continue;
        
        styleVar.m_IsVec2 ? ImGui::PushStyleVar(styleVar.m_Idx, styleVar.m_Value) : ImGui::PushStyleVar(styleVar.m_Idx, styleVar.m_Value.x);
    }

    for (const auto& styleColor : m_StyleColors)
    {
        if (styleColor.m_Idx == static_cast<ImGuiCol>(-1))
            continue;
        
        ImGui::PushStyleColor(styleColor.m_Idx, styleColor.m_Color);
    }

    bool anyOpen = false;
    for (auto& win : m_Windows)
    {
        if (!win.m_IsOpen) 
            continue;
        
        DrawWindow(win);
        
        if (win.m_IsOpen) 
            anyOpen = true;
    }

    if (!m_StyleColors.empty())
        ImGui::PopStyleColor(static_cast<int>(m_StyleColors.size()));
    
    if (!m_StyleVars.empty())
        ImGui::PopStyleVar(static_cast<int>(m_StyleVars.size()));

    if (!anyOpen)
        m_ShowCustomMenu = false;
}

void CImGuiCustomMenu::DrawWindow(MenuWindow& win)
{
    constexpr ImGuiWindowFlags kWinFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse;

    bool isOpen = win.m_IsOpen;
    const char* pTitle = win.m_Title.empty() ? m_DefaultTitle.c_str() : win.m_Title.c_str();

    if (!ImGui::Begin(pTitle, &isOpen, kWinFlags))
    {
        ImGui::End();
        win.m_IsOpen = isOpen;
        return;
    }

    const float scrW = static_cast<float>(g_ImGuiViewport.scrWidth());
    const float scrH = static_cast<float>(g_ImGuiViewport.scrHeight());

    ImVec2 winSize = ImGui::GetWindowSize();
    winSize.x = Q_min(winSize.x, scrW);
    winSize.y = Q_min(winSize.y, scrH);
    ImGui::SetWindowSize(winSize);

    ImVec2 winPos = ImGui::GetWindowPos();
    winPos.x = Q_max(0.0f, Q_min(winPos.x, scrW - winSize.x));
    winPos.y = Q_max(0.0f, Q_min(winPos.y, scrH - winSize.y));
    ImGui::SetWindowPos(winPos);

    DrawItemsRecursive(win.m_Items);

    ImGui::End();
    win.m_IsOpen = isOpen;
}

void CImGuiCustomMenu::DrawButton(MenuItem& item)
{
    if (item.m_Label.empty() || item.m_Command.empty()) 
        return;
    
    if (ImGui::Button(item.m_Label.c_str()))
        gEngfuncs.pfnClientCmd(item.m_Command.c_str());
}

void CImGuiCustomMenu::DrawCheckbox(MenuItem& item)
{
    if (item.m_Label.empty() || item.m_CvarName.empty()) 
        return;

    float cvarVal = gEngfuncs.pfnGetCvarFloat(item.m_CvarName.c_str());
    bool isActive = (cvarVal != 0.0f);

    if (ImGui::Checkbox(item.m_Label.c_str(), &isActive))
        m_ImguiUtils.SetCvarFloat(item.m_CvarName.c_str(), isActive ? 1.0f : 0.0f);
}

void CImGuiCustomMenu::DrawCloseMenu(MenuItem& item)
{
    if (item.m_Label.empty()) 
        return;
    
    if (ImGui::Button(item.m_Label.c_str()))
        m_ShowCustomMenu = false;
}

void CImGuiCustomMenu::DrawSubmenu(MenuItem& item)
{
    if (item.m_Label.empty()) 
        return;
    
    if (ImGui::CollapsingHeader(item.m_Label.c_str()))
    {
        ImGui::Indent(10.0f);
        DrawItemsRecursive(item.m_Children);
        ImGui::Unindent(10.0f);
    }
}

void CImGuiCustomMenu::DrawTabBar(MenuItem& item)
{
    if (item.m_Label.empty()) 
        return;

    const std::string tabBarId = item.m_Label + "##tabbar";
    if (!ImGui::BeginTabBar(tabBarId.c_str())) 
        return;

    for (auto& child : item.m_Children)
    {
        if (child.m_Type == MenuItemType::CONDITION)
        {
            const float condVal = gEngfuncs.pfnGetCvarFloat(child.m_ConditionCvar.c_str());
            if (condVal == child.m_ConditionValue)
            {
                for (auto& tabItem : child.m_Children)
                {
                    if (tabItem.m_Type != MenuItemType::TAB || tabItem.m_Label.empty())
                        continue;

                    if (ImGui::BeginTabItem(tabItem.m_Label.c_str()))
                    {
                        ImGui::PushID(&tabItem);
                        DrawItemsRecursive(tabItem.m_Children);
                        ImGui::PopID();
                        ImGui::EndTabItem();
                    }
                }
            }
            continue;
        }

        if (child.m_Type != MenuItemType::TAB || child.m_Label.empty())
            continue;

        if (ImGui::BeginTabItem(child.m_Label.c_str()))
        {
            ImGui::PushID(&child);
            DrawItemsRecursive(child.m_Children);
            ImGui::PopID();
            ImGui::EndTabItem();
        }
    }

    ImGui::EndTabBar();
}

void CImGuiCustomMenu::DrawSliderInt(MenuItem& item)
{
    if (item.m_Label.empty() || item.m_CvarName.empty()) 
        return;

    int sliderVal = static_cast<int>(gEngfuncs.pfnGetCvarFloat(item.m_CvarName.c_str()));

    if (ImGui::SliderInt(item.m_Label.c_str(), &sliderVal, item.m_MinInt, item.m_MaxInt))
    {
        char cmdBuf[256];
        std::snprintf(cmdBuf, sizeof(cmdBuf), "%s %d", item.m_CvarName.c_str(), sliderVal);
        gEngfuncs.pfnClientCmd(cmdBuf);
    }
}

void CImGuiCustomMenu::DrawSliderFloat(MenuItem& item)
{
    if (item.m_Label.empty() || item.m_CvarName.empty()) 
        return;

    constexpr float kStep = 0.1f;
    float sliderVal = gEngfuncs.pfnGetCvarFloat(item.m_CvarName.c_str());

    if (ImGui::SliderFloat(item.m_Label.c_str(), &sliderVal, item.m_MinValue, item.m_MaxValue, "%.1f"))
    {
        sliderVal = std::roundf(sliderVal / kStep) * kStep;

        char cmdBuf[256];
        std::snprintf(cmdBuf, sizeof(cmdBuf), "%s %.1f", item.m_CvarName.c_str(), sliderVal);
        gEngfuncs.pfnClientCmd(cmdBuf);
    }
}

void CImGuiCustomMenu::DrawColorCvar(MenuItem& item)
{
    if (item.m_Label.empty() || item.m_CvarName.empty()) 
        return;

    const char* pRawColor = gEngfuncs.pfnGetCvarString(item.m_CvarName.c_str());
    int r = 0, g = 0, b = 0, a = 255;
    int numParsed = 0;

    if (pRawColor && *pRawColor)
        numParsed = std::sscanf(pRawColor, "%d %d %d %d", &r, &g, &b, &a);

    if (numParsed < 3) 
    { 
        r = g = b = 0; 
        a = 255; 
    }

    if (numParsed < 4) 
    { 
        a = 255; 
    }

    float colArr[4] = {
        r / 255.0f, 
        g / 255.0f,
        b / 255.0f, 
        a / 255.0f
    };

    const bool hasAlpha  = (numParsed >= 4);
    const bool wasChanged = hasAlpha ? ImGui::ColorEdit4(item.m_Label.c_str(), colArr) : ImGui::ColorEdit3(item.m_Label.c_str(), colArr);

    if (wasChanged)
    {
        r = static_cast<int>(colArr[0] * 255.0f + 0.5f);
        g = static_cast<int>(colArr[1] * 255.0f + 0.5f);
        b = static_cast<int>(colArr[2] * 255.0f + 0.5f);
        a = static_cast<int>(colArr[3] * 255.0f + 0.5f);

        char cmdBuf[128];
        if (hasAlpha)
            std::snprintf(cmdBuf, sizeof(cmdBuf), "%s \"%d %d %d %d\"", item.m_CvarName.c_str(), r, g, b, a);
        else
            std::snprintf(cmdBuf, sizeof(cmdBuf), "%s \"%d %d %d\"",   item.m_CvarName.c_str(), r, g, b);

        gEngfuncs.pfnClientCmd(cmdBuf);
    }
}

void CImGuiCustomMenu::DrawCondition(MenuItem& item)
{
    const float cvarVal = gEngfuncs.pfnGetCvarFloat(item.m_ConditionCvar.c_str());
    bool isPassing = false;

    switch (item.m_ConditionOp)
    {
        case CompareOp::EQ: 
            isPassing = (cvarVal == item.m_ConditionValue); 
            break;
        
        case CompareOp::NE: 
            isPassing = (cvarVal != item.m_ConditionValue); 
            break;
        
        case CompareOp::GT: 
            isPassing = (cvarVal > item.m_ConditionValue); 
            break;
        
        case CompareOp::GE: 
            isPassing = (cvarVal >= item.m_ConditionValue); 
            break;
        
        case CompareOp::LT: 
            isPassing = (cvarVal < item.m_ConditionValue); 
            break;
        
        case CompareOp::LE: 
            isPassing = (cvarVal <= item.m_ConditionValue); 
            break;
    }

    if (isPassing)
        DrawItemsRecursive(item.m_Children);
}

void CImGuiCustomMenu::DrawImage(MenuItem& item)
{
    if (item.m_ImagePath.empty()) 
        return;

    if (!item.m_ImageLoaded)
    {
        item.m_Image = m_ImguiUtils.LoadImageFromFile(item.m_ImagePath.c_str());
        item.m_ImageLoaded = (item.m_Image.texture != ImTextureID{});

        if (!item.m_ImageLoaded)
        {
            gEngfuncs.Con_Printf("Failed to load image '%s'\n", item.m_ImagePath.c_str());
            return;
        }
    }

    const float imgW = (item.m_ImageWidth  > 0.0f) ? item.m_ImageWidth  : static_cast<float>(item.m_Image.width);
    const float imgH = (item.m_ImageHeight > 0.0f) ? item.m_ImageHeight : static_cast<float>(item.m_Image.height);

    ImGui::Image(item.m_Image.texture, ImVec2(imgW, imgH));
}

void CImGuiCustomMenu::DrawImageButton(MenuItem& item)
{
    if (item.m_ImagePath.empty()) 
        return;

    if (!item.m_ImageLoaded)
    {
        item.m_Image = m_ImguiUtils.LoadImageFromFile(item.m_ImagePath.c_str());
        item.m_ImageLoaded = (item.m_Image.texture != ImTextureID{});

        if (!item.m_ImageLoaded)
        {
            gEngfuncs.Con_Printf("Failed to load image '%s'\n", item.m_ImagePath.c_str());
            return;
        }
    }

    const float imgW = (item.m_ImageWidth  > 0.0f) ? item.m_ImageWidth : static_cast<float>(item.m_Image.width);
    const float imgH = (item.m_ImageHeight > 0.0f) ? item.m_ImageHeight : static_cast<float>(item.m_Image.height);

    ImGui::PushID(&item);
    const bool wasPressed = ImGui::ImageButton("##imgbtn", item.m_Image.texture, ImVec2(imgW, imgH));
    ImGui::PopID();

    if (wasPressed && !item.m_Command.empty())
        gEngfuncs.pfnClientCmd(item.m_Command.c_str());

    if (!item.m_Label.empty() && ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", item.m_Label.c_str());
}

void CImGuiCustomMenu::DrawCvarCheck(MenuItem& item)
{
    cvar_t* pCvar = gEngfuncs.pfnGetCvarPointer(item.m_CvarName.c_str());

    if (!pCvar)
    {
        ImGui::Text("%s: <not found>", item.m_Label.c_str());
        return;
    }

    char* pEnd = nullptr;
    std::strtof(pCvar->string, &pEnd);
    const bool isNumber = (pEnd && *pEnd == '\0');

    if (!isNumber)
    {
        ImGui::Text("%s: %s", item.m_Label.c_str(), pCvar->string);
        return;
    }

    const float floatVal = pCvar->value;
    const int intVal = static_cast<int>(floatVal);

    if (fabsf(floatVal - static_cast<float>(intVal)) < 0.0001f)
        ImGui::Text("%s: %d", item.m_Label.c_str(), intVal);
    else
        ImGui::Text("%s: %.3f", item.m_Label.c_str(), floatVal);
}

void CImGuiCustomMenu::DrawItemsRecursive(std::vector<MenuItem>& items)
{
    for (auto& item : items)
    {
        switch (item.m_Type)
        {
            case MenuItemType::BUTTON:       
                DrawButton(item);      
                break;
            
            case MenuItemType::CHECKBOX:     
                DrawCheckbox(item);    
                break;
            
            case MenuItemType::CLOSE_MENU:   
                DrawCloseMenu(item);   
                break;
            
            case MenuItemType::SUBMENU:      
                DrawSubmenu(item);     
                break;
            
            case MenuItemType::TABBAR:       
                DrawTabBar(item);      
                break;
            
            case MenuItemType::SLIDER_INT:   
                DrawSliderInt(item);   
                break;
            
            case MenuItemType::SLIDER_FLOAT: 
                DrawSliderFloat(item); 
                break;
            
            case MenuItemType::COLOR_CVAR:   
                DrawColorCvar(item);   
                break;
            
            case MenuItemType::CONDITION:    
                DrawCondition(item);   
                break;
            
            case MenuItemType::IMAGE:        
                DrawImage(item);
                break;
            
            case MenuItemType::IMAGE_BUTTON: 
                DrawImageButton(item); 
                break;
            
            case MenuItemType::CVAR_CHECK:   
                DrawCvarCheck(item);   
                break;
            
            case MenuItemType::TEXT:
                if (!item.m_Label.empty())
                    ImGui::TextUnformatted(item.m_Label.c_str());
                break;

            case MenuItemType::SEPARATOR:
                ImGui::Separator();
                break;

            case MenuItemType::SAME_LINE:
                ImGui::SameLine();
                break;

            case MenuItemType::SPACE:
                ImGui::Spacing();
                break;

            case MenuItemType::TAB:
                break;
        }
    }
}

ImGuiStyleVar CImGuiCustomMenu::GetStyleVarIndex(const std::string& name)
{
    auto it = s_StyleVarMap.find(name);
    return (it != s_StyleVarMap.end()) ? it->second : static_cast<ImGuiStyleVar>(-1);
}

ImGuiCol CImGuiCustomMenu::GetColorIndex(const std::string& name)
{
    auto it = s_ColorMap.find(name);
    return (it != s_ColorMap.end()) ? it->second : static_cast<ImGuiCol>(-1);
}

void CImGuiCustomMenu::SetupDefaultMenuStyle()
{
    auto addColor = [&](ImGuiCol colIdx, float r, float g, float b, float a)
    {
        m_StyleColors.push_back({colIdx, ImVec4(r, g, b, a)});
    };

    auto addVar = [&](ImGuiStyleVar varIdx, float val)
    {
        m_StyleVars.push_back({varIdx, ImVec2(val, 0.0f), false});
    };

    auto addVar2 = [&](ImGuiStyleVar varIdx, float x, float y)
    {
        m_StyleVars.push_back({varIdx, ImVec2(x, y), true});
    };

    addColor(ImGuiCol_Text,                      1.00f, 1.00f, 1.00f, 1.00f);
    addColor(ImGuiCol_TextDisabled,              0.50f, 0.50f, 0.50f, 1.00f);
    addColor(ImGuiCol_WindowBg,                  0.06f, 0.06f, 0.06f, 0.94f);
    addColor(ImGuiCol_ChildBg,                   0.00f, 0.00f, 0.00f, 0.00f);
    addColor(ImGuiCol_PopupBg,                   0.08f, 0.08f, 0.08f, 0.94f);
    addColor(ImGuiCol_Border,                    0.43f, 0.43f, 0.50f, 0.50f);
    addColor(ImGuiCol_BorderShadow,              0.00f, 0.00f, 0.00f, 0.00f);
    addColor(ImGuiCol_FrameBg,                   0.16f, 0.29f, 0.48f, 0.54f);
    addColor(ImGuiCol_FrameBgHovered,            0.26f, 0.59f, 0.98f, 0.40f);
    addColor(ImGuiCol_FrameBgActive,             0.26f, 0.59f, 0.98f, 0.67f);
    addColor(ImGuiCol_TitleBg,                   0.04f, 0.04f, 0.04f, 1.00f);
    addColor(ImGuiCol_TitleBgActive,             0.16f, 0.29f, 0.48f, 1.00f);
    addColor(ImGuiCol_TitleBgCollapsed,          0.00f, 0.00f, 0.00f, 0.51f);
    addColor(ImGuiCol_MenuBarBg,                 0.14f, 0.14f, 0.14f, 1.00f);
    addColor(ImGuiCol_ScrollbarBg,               0.02f, 0.02f, 0.02f, 0.53f);
    addColor(ImGuiCol_ScrollbarGrab,             0.31f, 0.31f, 0.31f, 1.00f);
    addColor(ImGuiCol_ScrollbarGrabHovered,      0.41f, 0.41f, 0.41f, 1.00f);
    addColor(ImGuiCol_ScrollbarGrabActive,       0.51f, 0.51f, 0.51f, 1.00f);
    addColor(ImGuiCol_CheckMark,                 0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_SliderGrab,                0.24f, 0.52f, 0.88f, 1.00f);
    addColor(ImGuiCol_SliderGrabActive,          0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_Button,                    0.26f, 0.59f, 0.98f, 0.40f);
    addColor(ImGuiCol_ButtonHovered,             0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_ButtonActive,              0.06f, 0.53f, 0.98f, 1.00f);
    addColor(ImGuiCol_Header,                    0.26f, 0.59f, 0.98f, 0.31f);
    addColor(ImGuiCol_HeaderHovered,             0.26f, 0.59f, 0.98f, 0.80f);
    addColor(ImGuiCol_HeaderActive,              0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_Separator,                 0.43f, 0.43f, 0.50f, 0.50f);
    addColor(ImGuiCol_SeparatorHovered,          0.10f, 0.40f, 0.75f, 0.78f);
    addColor(ImGuiCol_SeparatorActive,           0.10f, 0.40f, 0.75f, 1.00f);
    addColor(ImGuiCol_ResizeGrip,                0.26f, 0.59f, 0.98f, 0.20f);
    addColor(ImGuiCol_ResizeGripHovered,         0.26f, 0.59f, 0.98f, 0.67f);
    addColor(ImGuiCol_ResizeGripActive,          0.26f, 0.59f, 0.98f, 0.95f);
    addColor(ImGuiCol_InputTextCursor,           1.00f, 1.00f, 1.00f, 1.00f);
    addColor(ImGuiCol_TabHovered,                0.26f, 0.59f, 0.98f, 0.80f);
    addColor(ImGuiCol_Tab,                       0.18f, 0.35f, 0.58f, 0.86f);
    addColor(ImGuiCol_TabSelected,               0.20f, 0.41f, 0.68f, 1.00f);
    addColor(ImGuiCol_TabSelectedOverline,       0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_TabDimmed,                 0.07f, 0.10f, 0.15f, 0.97f);
    addColor(ImGuiCol_TabDimmedSelected,         0.14f, 0.26f, 0.42f, 1.00f);
    addColor(ImGuiCol_TabDimmedSelectedOverline, 0.50f, 0.50f, 0.50f, 0.00f);
    addColor(ImGuiCol_PlotLines,                 0.61f, 0.61f, 0.61f, 1.00f);
    addColor(ImGuiCol_PlotLinesHovered,          1.00f, 0.43f, 0.35f, 1.00f);
    addColor(ImGuiCol_PlotHistogram,             0.90f, 0.70f, 0.00f, 1.00f);
    addColor(ImGuiCol_PlotHistogramHovered,      1.00f, 0.60f, 0.00f, 1.00f);
    addColor(ImGuiCol_TableHeaderBg,             0.19f, 0.19f, 0.20f, 1.00f);
    addColor(ImGuiCol_TableBorderStrong,         0.31f, 0.31f, 0.35f, 1.00f);
    addColor(ImGuiCol_TableBorderLight,          0.23f, 0.23f, 0.25f, 1.00f);
    addColor(ImGuiCol_TableRowBg,                0.00f, 0.00f, 0.00f, 0.00f);
    addColor(ImGuiCol_TableRowBgAlt,             1.00f, 1.00f, 1.00f, 0.06f);
    addColor(ImGuiCol_TextLink,                  0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_TextSelectedBg,            0.26f, 0.59f, 0.98f, 0.35f);
    addColor(ImGuiCol_TreeLines,                 0.43f, 0.43f, 0.50f, 0.50f);
    addColor(ImGuiCol_DragDropTarget,            1.00f, 1.00f, 0.00f, 0.90f);
    addColor(ImGuiCol_UnsavedMarker,             1.00f, 1.00f, 1.00f, 1.00f);
    addColor(ImGuiCol_NavCursor,                 0.26f, 0.59f, 0.98f, 1.00f);
    addColor(ImGuiCol_NavWindowingHighlight,     1.00f, 1.00f, 1.00f, 0.70f);
    addColor(ImGuiCol_NavWindowingDimBg,         0.80f, 0.80f, 0.80f, 0.20f);
    addColor(ImGuiCol_ModalWindowDimBg,          0.80f, 0.80f, 0.80f, 0.35f);

    addVar (ImGuiStyleVar_Alpha,                      1.00f);
    addVar (ImGuiStyleVar_DisabledAlpha,              0.60f);
    addVar (ImGuiStyleVar_WindowRounding,             0.00f);
    addVar (ImGuiStyleVar_WindowBorderSize,           1.00f);
    addVar (ImGuiStyleVar_ChildRounding,              0.00f);
    addVar (ImGuiStyleVar_ChildBorderSize,            1.00f);
    addVar (ImGuiStyleVar_PopupRounding,              0.00f);
    addVar (ImGuiStyleVar_PopupBorderSize,            1.00f);
    addVar (ImGuiStyleVar_FrameRounding,              0.00f);
    addVar (ImGuiStyleVar_FrameBorderSize,            0.00f);
    addVar (ImGuiStyleVar_IndentSpacing,             21.00f);
    addVar (ImGuiStyleVar_ScrollbarSize,             14.00f);
    addVar (ImGuiStyleVar_ScrollbarRounding,          9.00f);
    addVar (ImGuiStyleVar_ScrollbarPadding,           2.00f);
    addVar (ImGuiStyleVar_GrabMinSize,               12.00f);
    addVar (ImGuiStyleVar_GrabRounding,               0.00f);
    addVar (ImGuiStyleVar_ImageBorderSize,            0.00f);
    addVar (ImGuiStyleVar_TabRounding,                5.00f);
    addVar (ImGuiStyleVar_TabBorderSize,              0.00f);
    addVar (ImGuiStyleVar_TabMinWidthBase,            1.00f);
    addVar (ImGuiStyleVar_TabMinWidthShrink,         80.00f);
    addVar (ImGuiStyleVar_TabBarBorderSize,           1.00f);
    addVar (ImGuiStyleVar_TabBarOverlineSize,         1.00f);
    addVar (ImGuiStyleVar_TableAngledHeadersAngle,    0.610865f);
    addVar (ImGuiStyleVar_TreeLinesSize,              1.00f);
    addVar (ImGuiStyleVar_TreeLinesRounding,          0.00f);
    addVar (ImGuiStyleVar_SeparatorTextBorderSize,    3.00f);

    addVar2(ImGuiStyleVar_WindowPadding,               8.0f,  8.0f);
    addVar2(ImGuiStyleVar_WindowMinSize,              32.0f, 32.0f);
    addVar2(ImGuiStyleVar_WindowTitleAlign,            0.0f,  0.5f);
    addVar2(ImGuiStyleVar_FramePadding,                4.0f,  3.0f);
    addVar2(ImGuiStyleVar_ItemSpacing,                 8.0f,  4.0f);
    addVar2(ImGuiStyleVar_ItemInnerSpacing,            4.0f,  4.0f);
    addVar2(ImGuiStyleVar_CellPadding,                 4.0f,  2.0f);
    addVar2(ImGuiStyleVar_TableAngledHeadersTextAlign, 0.5f,  0.0f);
    addVar2(ImGuiStyleVar_ButtonTextAlign,             0.5f,  0.5f);
    addVar2(ImGuiStyleVar_SelectableTextAlign,         0.0f,  0.0f);
    addVar2(ImGuiStyleVar_SeparatorTextAlign,          0.0f,  0.5f);
    addVar2(ImGuiStyleVar_SeparatorTextPadding,       20.0f,  3.0f);
}

void CImGuiCustomMenu::FreeImagesRecursive(std::vector<MenuItem>& items)
{
    for (auto& item : items)
    {
        if ((item.m_Type == MenuItemType::IMAGE || item.m_Type == MenuItemType::IMAGE_BUTTON) && item.m_Image.texture != ImTextureID{})
        {
            m_ImguiUtils.FreeImage(item.m_Image);
            item.m_ImageLoaded = false;
        }

        if (!item.m_Children.empty())
            FreeImagesRecursive(item.m_Children);
    }
}

void CImGuiCustomMenu::FreeAllImages()
{
    for (auto& win : m_Windows)
        FreeImagesRecursive(win.m_Items);
}

void CImGuiCustomMenu::ExecMenu_f()
{
    if (gEngfuncs.Cmd_Argc() < 2)
    {
        gEngfuncs.Con_Printf("Usage: exec_menu <file>\n");
        return;
    }

    std::string filePath = gEngfuncs.Cmd_Argv(1);

    if (filePath.size() < 4 ||
        filePath.compare(filePath.size() - 4, 4, ".cfg") != 0)
        filePath += ".cfg";

    if (!LoadFromCfg(filePath.c_str()))
        gEngfuncs.Con_Printf("Failed to load menu '%s'\n", filePath.c_str());
}

bool CImGuiCustomMenu::LoadFromCfg(const char* pFilename)
{
    FreeAllImages();
    m_ShowCustomMenu = false;

    char fullPath[512];
    std::snprintf(fullPath, sizeof(fullPath), "%s/custom_menu/%s", gEngfuncs.pfnGetGameDirectory(), pFilename);

    FILE* pFile = std::fopen(fullPath, "r");
    if (!pFile)
    {
        gEngfuncs.Con_Printf("Cannot open menu config: %s\n", fullPath);
        return false;
    }

    m_Windows.clear();
    m_StyleVars.clear();
    m_StyleColors.clear();
    SetupDefaultMenuStyle();

    MenuWindow* pCurWin = nullptr;
    std::vector<MenuItem>* pCurList = nullptr;
    MenuItem* pLastContainer = nullptr;

    std::vector<std::vector<MenuItem>*> blockStack;

    bool hadError = false;
    int lineNum  = 0;

    auto PrintError = [&](const char* pFmt, ...)
    {
        hadError = true;
        char msgBuf[1024];
        va_list args;
        va_start(args, pFmt);
        std::vsnprintf(msgBuf, sizeof(msgBuf), pFmt, args);
        va_end(args);
        gEngfuncs.Con_Printf("Menu cfg error in %s:%d: %s\n", fullPath, lineNum, msgBuf);
    };

    auto PushContainer = [&]()
    {
        if (pLastContainer && pCurList)
        {
            blockStack.push_back(pCurList);
            pCurList       = &pLastContainer->m_Children;
            pLastContainer = nullptr;
        }
    };

    auto ParseContainerItem = [&](const std::string& str, MenuItemType itemType, const char* pHint) -> bool
    {
        std::string label;
        if (!ExtractQuoted(str, {&label}))
        {
            PrintError("Invalid %s syntax. Expected: %s \"Label\" { ... }", pHint, pHint);
            return false;
        }

        MenuItem newItem;
        newItem.m_Type  = itemType;
        newItem.m_Label = label;
        pCurList->push_back(newItem);
        pLastContainer = &pCurList->back();

        size_t openQuotePos  = str.find('"');
        size_t closeQuotePos = str.find('"', openQuotePos + 1);
        if (str.find('{', closeQuotePos) != std::string::npos)
            PushContainer();

        return true;
    };

    char lineBuf[512];
    while (std::fgets(lineBuf, sizeof(lineBuf), pFile))
    {
        ++lineNum;
        TrimRight(lineBuf);
        if (lineBuf[0] == '\0') continue;

        std::string str(lineBuf);
        TrimLeft(str);
        if (str.empty()) continue;

        if (str[0] == '#' || str[0] == ';' || (str.size() > 1 && str[0] == '/' && str[1] == '/'))
            continue;

        if (!pCurWin)
        {
            if (StartsWith(str, "stylevar2"))
            {
                char varName[64]; float valX, valY;
                if (std::sscanf(str.c_str(), "stylevar2 %63s %f %f", varName, &valX, &valY) != 3)
                { 
                    PrintError("Invalid stylevar2 syntax"); 
                    continue; 
                }

                ImGuiStyleVar varIdx = GetStyleVarIndex(varName);
                if (varIdx == static_cast<ImGuiStyleVar>(-1))
                { 
                    PrintError("Unknown stylevar2 '%s'", varName); 
                    continue; 
                }

                m_StyleVars.push_back({varIdx, ImVec2(valX, valY), true});
                continue;
            }

            if (StartsWith(str, "stylevar"))
            {
                char varName[64]; float valX;
                if (std::sscanf(str.c_str(), "stylevar %63s %f", varName, &valX) != 2)
                { 
                    PrintError("Invalid stylevar syntax"); 
                    continue; 
                }

                ImGuiStyleVar varIdx = GetStyleVarIndex(varName);
                if (varIdx == static_cast<ImGuiStyleVar>(-1))
                { 
                    PrintError("Unknown stylevar '%s'", varName); 
                    continue; 
                }

                m_StyleVars.push_back({varIdx, ImVec2(valX, 0.0f), false});
                continue;
            }

            if (StartsWith(str, "stylecolor"))
            {
                char colName[64]; float r, g, b, a;
                if (std::sscanf(str.c_str(), "stylecolor %63s %f %f %f %f", colName, &r, &g, &b, &a) != 5)
                    { 
                        PrintError("Invalid stylecolor syntax"); 
                        continue; 
                    }

                ImGuiCol colIdx = GetColorIndex(colName);
                if (colIdx == static_cast<ImGuiCol>(-1))
                { 
                    PrintError("Unknown stylecolor '%s'", colName); 
                    continue; 
                }

                m_StyleColors.push_back({colIdx, ImVec4(r, g, b, a)});
                continue;
            }

            if (StartsWith(str, "window"))
            {
                std::string winTitle;
                MenuWindow  newWin;

                if (!ExtractQuoted(str, {&winTitle}))
                    PrintError("Window title is missing. Using default title."); 
                else
                    newWin.m_Title = winTitle;

                m_Windows.push_back(newWin);
                pCurWin = &m_Windows.back();
                pCurList = &pCurWin->m_Items;
                pLastContainer = nullptr;
                blockStack.clear();
                continue;
            }

            if (str == "{" || str == "}")
            { 
                PrintError("Unexpected '%s' before any window", str.c_str()); 
                continue; 
            }

            PrintError("Unknown directive before any window: '%s'", str.c_str());
            continue;
        }

        if (str == "}")
        {
            if (!blockStack.empty())
            {
                pCurList = blockStack.back();
                blockStack.pop_back();
                pLastContainer = nullptr;
            }
            else
            {
                pCurWin = nullptr;
                pCurList = nullptr;
                pLastContainer = nullptr;
            }
            continue;
        }

        if (str == "{")
        {
            PushContainer();
            continue;
        }

        if (!pCurList)
        {
            PrintError("Internal parser error: pCurList is null");
            continue;
        }

        if (StartsWith(str, "text"))
        {
            std::string label;
            if (!ExtractQuoted(str, {&label}))
            { 
                PrintError("Invalid text syntax. Expected: text \"Label\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::TEXT;
            newItem.m_Label = label;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "separator"))
        {
            MenuItem newItem;
            newItem.m_Type = MenuItemType::SEPARATOR;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "same_line"))
        {
            MenuItem newItem;
            newItem.m_Type = MenuItemType::SAME_LINE;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "space"))
        {
            MenuItem newItem;
            newItem.m_Type = MenuItemType::SPACE;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "button"))
        {
            std::string label, cmd;
            if (!ExtractQuoted(str, {&label, &cmd}))
            { 
                PrintError("Invalid button syntax. Expected: button \"Label\" \"command\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::BUTTON;
            newItem.m_Label = label;
            newItem.m_Command = cmd;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "checkbox"))
        {
            std::string label, cvarName;
            if (!ExtractQuoted(str, {&label, &cvarName}))
            { 
                PrintError("Invalid checkbox syntax. Expected: checkbox \"Label\" \"cvar\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::CHECKBOX;
            newItem.m_Label = label;
            newItem.m_CvarName = cvarName;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "close_menu"))
        {
            std::string label;
            if (!ExtractQuoted(str, {&label}))
            { 
                PrintError("Invalid close_menu syntax. Expected: close_menu \"Label\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::CLOSE_MENU;
            newItem.m_Label = label;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "submenu"))
        {
            ParseContainerItem(str, MenuItemType::SUBMENU, "submenu");
            continue;
        }

        if (StartsWith(str, "tabbar"))
        {
            ParseContainerItem(str, MenuItemType::TABBAR, "tabbar");
            continue;
        }

        if (StartsWith(str, "tab"))
        {
            ParseContainerItem(str, MenuItemType::TAB, "tab");
            continue;
        }

        if (StartsWith(str, "slider_int"))
        {
            std::string label, cvarName;
            if (!ExtractQuoted(str, {&label, &cvarName}))
            { 
                PrintError("Invalid slider_int syntax"); 
                continue; 
            }

            const size_t lastQuotePos = str.rfind('"');
            int minVal = 0, maxVal = 0;
            if (lastQuotePos == std::string::npos || std::sscanf(str.c_str() + lastQuotePos + 1, "%d %d", &minVal, &maxVal) != 2)
            { 
                PrintError("Invalid slider_int range"); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::SLIDER_INT;
            newItem.m_Label = label;
            newItem.m_CvarName = cvarName;
            newItem.m_MinInt = minVal;
            newItem.m_MaxInt = maxVal;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "slider_float"))
        {
            std::string label, cvarName;
            if (!ExtractQuoted(str, {&label, &cvarName}))
            { 
                PrintError("Invalid slider_float syntax"); 
                continue; 
            }

            const size_t lastQuotePos = str.rfind('"');
            float minVal = 0.0f, maxVal = 0.0f;
            if (lastQuotePos == std::string::npos || std::sscanf(str.c_str() + lastQuotePos + 1, "%f %f", &minVal, &maxVal) != 2)
            { 
                PrintError("Invalid slider_float range"); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::SLIDER_FLOAT;
            newItem.m_Label = label;
            newItem.m_CvarName = cvarName;
            newItem.m_MinValue = minVal;
            newItem.m_MaxValue = maxVal;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "color_cvar"))
        {
            std::string label, cvarName;
            if (!ExtractQuoted(str, {&label, &cvarName}))
            { 
                PrintError("Invalid color_cvar syntax. Expected: color_cvar \"Label\" \"cvar\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::COLOR_CVAR;
            newItem.m_Label = label;
            newItem.m_CvarName = cvarName;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "cvar_check"))
        {
            std::string label, cvarName;
            if (!ExtractQuoted(str, {&label, &cvarName}))
            { 
                PrintError("Invalid cvar_check syntax. Expected: cvar_check \"Label\" \"cvar\""); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::CVAR_CHECK;
            newItem.m_Label = label;
            newItem.m_CvarName = cvarName;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "condition"))
        {
            std::string cvarName;
            if (!ExtractQuoted(str, {&cvarName}))
            { 
                PrintError("Invalid condition syntax"); 
                continue; 
             }

            const size_t lastQuotePos = str.rfind('"');
            std::string restStr = str.substr(lastQuotePos + 1);

            MenuItem newItem;
            newItem.m_Type = MenuItemType::CONDITION;
            newItem.m_ConditionCvar = cvarName;

            if (restStr.find(">=") != std::string::npos) 
            {
                newItem.m_ConditionOp = CompareOp::GE;
            }
            else if (restStr.find("<=") != std::string::npos) 
            {
                newItem.m_ConditionOp = CompareOp::LE;
            }
            else if (restStr.find("!=") != std::string::npos) 
            {
                newItem.m_ConditionOp = CompareOp::NE;
            }
            else if (restStr.find('>') != std::string::npos) 
            {
                newItem.m_ConditionOp = CompareOp::GT;
            }
            else if (restStr.find('<') != std::string::npos) 
            {
                newItem.m_ConditionOp = CompareOp::LT;
            }
            else                                               
            {
                newItem.m_ConditionOp = CompareOp::EQ;
            }

            float condVal = 0.0f;
            if (std::sscanf(restStr.c_str(), " %*[^0-9.-]%f", &condVal) != 1 && std::sscanf(restStr.c_str(), " %f",            &condVal) != 1)
            { 
                PrintError("Invalid condition value"); 
                continue; 
            }

            newItem.m_ConditionValue = condVal;
            pCurList->push_back(newItem);
            pLastContainer = &pCurList->back();

            if (str.find('{', lastQuotePos) != std::string::npos)
                PushContainer();

            continue;
        }

        if (StartsWith(str, "image_button"))
        {
            std::string label, cmd, imgPath;
            if (!ExtractQuoted(str, {&label, &cmd, &imgPath}))
            {
                PrintError("Invalid image_button syntax. Expected: image_button \"Label\" \"command\" \"image\" w h");
                continue;
            }

            const size_t lastQuotePos = str.rfind('"');
            float imgW = 32.0f, imgH = 32.0f;
            std::sscanf(str.c_str() + lastQuotePos + 1, "%f %f", &imgW, &imgH);

            MenuItem newItem;
            newItem.m_Type = MenuItemType::IMAGE_BUTTON;
            newItem.m_Label = label;
            newItem.m_Command = cmd;
            newItem.m_ImagePath = imgPath;
            newItem.m_ImageWidth = imgW;
            newItem.m_ImageHeight = imgH;
            newItem.m_ImageLoaded = false;
            pCurList->push_back(newItem);
            continue;
        }

        if (StartsWith(str, "image "))
        {
            std::string imgPath;
            if (!ExtractQuoted(str, {&imgPath}))
            { 
                PrintError("Invalid image syntax. Expected: image \"path\" width height"); 
                continue; 
            }

            const size_t lastQuotePos = str.rfind('"');
            float imgW = 0.0f, imgH = 0.0f;
            if (std::sscanf(str.c_str() + lastQuotePos + 1, "%f %f", &imgW, &imgH) != 2)
            { 
                PrintError("Invalid image size"); 
                continue; 
            }

            MenuItem newItem;
            newItem.m_Type = MenuItemType::IMAGE;
            newItem.m_ImagePath = imgPath;
            newItem.m_ImageWidth = imgW;
            newItem.m_ImageHeight = imgH;
            newItem.m_ImageLoaded = false;
            pCurList->push_back(newItem);
            continue;
        }

        PrintError("Unknown directive: '%s'", str.c_str());
    }

    std::fclose(pFile);

    if (!blockStack.empty())
        PrintError("Unexpected end of file: %d unclosed '{' block(s)", static_cast<int>(blockStack.size()));

    const bool isSuccess = !hadError && blockStack.empty() && !m_Windows.empty();
    m_ShowCustomMenu = isSuccess;
    return isSuccess;
}
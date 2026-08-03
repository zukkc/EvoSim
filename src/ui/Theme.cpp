#include "Theme.h"

#include <imgui.h>

namespace Theme
{

void apply_evosim_theme()
{
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    // Rozmiary i odstępy
    style.WindowPadding = {12.0f, 10.0f};
    style.FramePadding = {9.0f, 5.0f};
    style.CellPadding = {8.0f, 5.0f};

    style.ItemSpacing = {8.0f, 7.0f};
    style.ItemInnerSpacing = {6.0f, 4.0f};

    style.IndentSpacing = 20.0f;
    style.ScrollbarSize = 13.0f;
    style.GrabMinSize = 10.0f;

    // Zaokrąglenia
    style.WindowRounding = 6.0f;
    style.ChildRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    // Ramki
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.TabBorderSize = 0.0f;

    style.WindowTitleAlign = {0.0f, 0.5f};

    ImVec4* colors = style.Colors;

    // Tło
    colors[ImGuiCol_WindowBg] =
        {0.045f, 0.055f, 0.070f, 1.00f};

    colors[ImGuiCol_ChildBg] =
        {0.055f, 0.065f, 0.082f, 1.00f};

    colors[ImGuiCol_PopupBg] =
        {0.060f, 0.072f, 0.090f, 0.98f};

    colors[ImGuiCol_MenuBarBg] =
        {0.050f, 0.060f, 0.075f, 1.00f};

    // Tekst
    colors[ImGuiCol_Text] =
        {0.90f, 0.93f, 0.96f, 1.00f};

    colors[ImGuiCol_TextDisabled] =
        {0.45f, 0.50f, 0.56f, 1.00f};

    // Obramowania
    colors[ImGuiCol_Border] =
        {0.15f, 0.18f, 0.22f, 1.00f};

    colors[ImGuiCol_BorderShadow] =
        {0.00f, 0.00f, 0.00f, 0.00f};

    // Pola tekstowe, suwaki itd.
    colors[ImGuiCol_FrameBg] =
        {0.085f, 0.10f, 0.125f, 1.00f};

    colors[ImGuiCol_FrameBgHovered] =
        {0.12f, 0.16f, 0.19f, 1.00f};

    colors[ImGuiCol_FrameBgActive] =
        {0.14f, 0.20f, 0.24f, 1.00f};

    // Kolor przewodni
    constexpr ImVec4 accent{
        0.10f, 0.68f, 0.74f, 1.00f
    };

    constexpr ImVec4 accent_hovered{
        0.14f, 0.78f, 0.83f, 1.00f
    };

    constexpr ImVec4 accent_active{
        0.08f, 0.55f, 0.62f, 1.00f
    };

    colors[ImGuiCol_CheckMark] = accent;
    colors[ImGuiCol_SliderGrab] = accent;
    colors[ImGuiCol_SliderGrabActive] = accent_hovered;

    // Przyciski
    colors[ImGuiCol_Button] =
        {0.08f, 0.25f, 0.28f, 1.00f};

    colors[ImGuiCol_ButtonHovered] =
        {0.10f, 0.38f, 0.42f, 1.00f};

    colors[ImGuiCol_ButtonActive] =
        {0.08f, 0.48f, 0.52f, 1.00f};

    // Selectable, tree node, collapsing header
    colors[ImGuiCol_Header] =
        {0.08f, 0.22f, 0.25f, 1.00f};

    colors[ImGuiCol_HeaderHovered] =
        {0.10f, 0.34f, 0.38f, 1.00f};

    colors[ImGuiCol_HeaderActive] =
        {0.10f, 0.44f, 0.48f, 1.00f};

    // Pasek tytułowy
    colors[ImGuiCol_TitleBg] =
        {0.045f, 0.055f, 0.070f, 1.00f};

    colors[ImGuiCol_TitleBgActive] =
        {0.060f, 0.075f, 0.092f, 1.00f};

    colors[ImGuiCol_TitleBgCollapsed] =
        colors[ImGuiCol_TitleBg];

    // Zakładki
    colors[ImGuiCol_Tab] =
        {0.060f, 0.075f, 0.092f, 1.00f};

    colors[ImGuiCol_TabHovered] =
        {0.10f, 0.34f, 0.38f, 1.00f};

    colors[ImGuiCol_TabSelected] =
        {0.08f, 0.25f, 0.28f, 1.00f};

    colors[ImGuiCol_TabSelectedOverline] = accent;

    colors[ImGuiCol_TabDimmed] =
        {0.045f, 0.055f, 0.070f, 1.00f};

    colors[ImGuiCol_TabDimmedSelected] =
        {0.065f, 0.12f, 0.14f, 1.00f};

    // Separatory i resizing
    colors[ImGuiCol_Separator] =
        {0.15f, 0.18f, 0.22f, 1.00f};

    colors[ImGuiCol_SeparatorHovered] = accent_hovered;
    colors[ImGuiCol_SeparatorActive] = accent;

    colors[ImGuiCol_ResizeGrip] =
        {accent.x, accent.y, accent.z, 0.20f};

    colors[ImGuiCol_ResizeGripHovered] =
        {accent.x, accent.y, accent.z, 0.65f};

    colors[ImGuiCol_ResizeGripActive] = accent;

    // Tabele
    colors[ImGuiCol_TableHeaderBg] =
        {0.075f, 0.09f, 0.11f, 1.00f};

    colors[ImGuiCol_TableBorderStrong] =
        {0.16f, 0.19f, 0.23f, 1.00f};

    colors[ImGuiCol_TableBorderLight] =
        {0.11f, 0.13f, 0.16f, 1.00f};

    colors[ImGuiCol_TableRowBg] =
        {0.00f, 0.00f, 0.00f, 0.00f};

    colors[ImGuiCol_TableRowBgAlt] =
        {1.00f, 1.00f, 1.00f, 0.025f};

    // Docking
    colors[ImGuiCol_DockingPreview] =
        {accent.x, accent.y, accent.z, 0.65f};

    colors[ImGuiCol_DockingEmptyBg] =
        {0.035f, 0.043f, 0.055f, 1.00f};

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] =
        {0.035f, 0.043f, 0.055f, 1.00f};

    colors[ImGuiCol_ScrollbarGrab] =
        {0.16f, 0.19f, 0.23f, 1.00f};

    colors[ImGuiCol_ScrollbarGrabHovered] =
        {0.23f, 0.27f, 0.32f, 1.00f};

    colors[ImGuiCol_ScrollbarGrabActive] =
        {0.30f, 0.35f, 0.40f, 1.00f};
}

}
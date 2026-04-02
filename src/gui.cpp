#include "imgui.h"
#include "raylib.h"

#include "gui.hpp"

void gui::render(State& state) {
    // Settings panel collapse
    if (state.settings_trigger) {
        ImGui::SetNextWindowCollapsed(state.settings_collapse);
        state.settings_trigger = false;
    }

    // Settings panel initialization
    ImGui::Begin("Simulation Settings [S]", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowPos(ImVec2(config::settings_pos_x, config::settings_pos_y), ImGuiCond_FirstUseEver);
    ImGui::SetWindowCollapsed(state.settings_collapse, ImGuiCond_FirstUseEver);
    state.settings_collapse = ImGui::IsWindowCollapsed();

    // FPS counter
    ImGui::Text("FPS: %d", GetFPS());

    // Control buttons
    ImGui::SeparatorText("Controls");

    // Quit button
    if (ImGui::Button("Quit [Q]"))
        state.is_running = false;

    // Reset button
    ImGui::SameLine();
    if (ImGui::Button("Reset [R]"))
        state::reset(state);

    // Play/Pause button
    ImGui::SameLine();
    if (ImGui::Button(state.is_paused ? "Play [SPACE]" : "Pause [SPACE]"))
        state.is_paused = !state.is_paused;

    ImGui::End();
}

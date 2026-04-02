#include "imgui.h"
#include "rlImGui.h"

#include "camera.hpp"
#include "gui.hpp"
#include "simulation.hpp"
#include "theme.hpp"
#include "utils.hpp"

/**
 * @brief Handle application mouse and keyboard input.
 * @param state Current simulation state.
 */
static void handle_input(State& state) {
    // Quit simulation
    if (IsKeyPressed(KEY_Q))
        state.is_running = false;

    // Reset simulation
    if (IsKeyPressed(KEY_R))
        state::reset(state);

    // Toggle pause
    if (IsKeyPressed(KEY_SPACE))
        state.is_paused = !state.is_paused;

    // Toggle settings panel
    if (IsKeyPressed(KEY_S)) {
        state.settings_collapse = !state.settings_collapse;
        state.settings_trigger = true;
    }
}

/**
 * @brief Application entry point.
 * @returns Exit code.
 */
int main() {
    // Initialize raylib
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(config::screen_width, config::screen_height, config::title);
    SetTargetFPS(config::fps);

    // Set resources directory and app icon
    bool found = utils::set_resource_dir("resources");
    if (found) {
        Image icon = LoadImage("icon.png");
        SetWindowIcon(icon);
    } else {
        TraceLog(LOG_WARNING, "Unable to set resources directory");
    }

    // Initialize ImGui
    rlImGuiSetup(true);
    theme::apply();

    // Disable imgui.ini
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;

    // Initialize camera
    Camera2D camera = {};
    camera::reset(camera);

    // Initialize simulation state
    State state = {};
    state::reset(state);

    while (state.is_running && !WindowShouldClose()) {
        // Logic
        handle_input(state);
        camera::update(camera);
        simulation::update(state);

        BeginDrawing();
        ClearBackground(theme::bg0);

        // Draw
        BeginMode2D(camera);
        simulation::draw(state);
        EndMode2D();

        // GUI
        rlImGuiBegin();
        gui::render(state);
        rlImGuiEnd();

        EndDrawing();
    }

    // Cleanup
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}

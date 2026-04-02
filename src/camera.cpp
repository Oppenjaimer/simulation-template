#include "imgui.h"

#include "camera.hpp"
#include "config.hpp"

#include "raymath.h" // Include after raylib.h

/**
 * @brief Handle camera panning with specific delta vector.
 * @param camera Camera to modify.
 * @param delta Movement vector.
 * @param mouse Whether the input is from a mouse or keyboard.
 */
static void pan(Camera2D& camera, Vector2 delta, bool mouse) {
    float sensitivity = mouse ? config::pan_sensitivity_mouse : config::pan_sensitivity_keyboard;
    delta *= -sensitivity / camera.zoom;
    camera.target += delta;
}

/**
 * @brief Handle camera panning via left mouse click and drag.
 * @param camera Camera to modify.
 */
static void pan(Camera2D& camera) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        pan(camera, GetMouseDelta(), true);
}

/**
 * @brief Handle camera zooming with logarithmic scale.
 * @param camera Camera to modify.
 * @param value Zoom direction and amount.
 * @param mouse Whether the input is from a mouse or keyboard.
 */
static void zoom(Camera2D& camera, float value, bool mouse) {
    float sensitivity = mouse ? config::zoom_sensitivity_mouse : config::zoom_sensitivity_keyboard;
    float scale = sensitivity * value;
    camera.zoom = Clamp(expf(logf(camera.zoom) + scale), config::zoom_min, config::zoom_max);
}

/**
 * @brief Handle camera zooming via mouse wheel.
 * @param camera Camera to modify.
 */
static void zoom(Camera2D& camera) {
    float wheel = GetMouseWheelMove();
    if (wheel == 0) return;

    // Make cursor point match in screen space and world space
    Vector2 mouse_world = GetScreenToWorld2D(GetMousePosition(), camera);
    camera.offset = GetMousePosition();
    camera.target = mouse_world;

    zoom(camera, wheel, true);
}

void camera::update(Camera2D& camera) {
    ImGuiIO& io = ImGui::GetIO();

    // Window resize
    if (IsWindowResized())
        camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    // Mouse camera controls (only when not in UI)
    if (!io.WantCaptureMouse) {
        pan(camera);
        zoom(camera);
    }

    // Keyboard camera controls (only when not in UI)
    if (!io.WantCaptureKeyboard) {
        // Pan
        Vector2 delta = {0, 0};
        if (IsKeyDown(KEY_UP)) delta.y = 1;
        if (IsKeyDown(KEY_DOWN)) delta.y = -1;
        if (IsKeyDown(KEY_LEFT)) delta.x = 1;
        if (IsKeyDown(KEY_RIGHT)) delta.x = -1;
        pan(camera, delta, false);

        // Zoom
        Vector2 center_screen = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        Vector2 center_world = GetScreenToWorld2D(center_screen, camera);
        camera.offset = center_screen;
        camera.target = center_world;
        float value = 0.0f;
        if (IsKeyDown(KEY_SLASH)) value = -1.0f;
        if (IsKeyDown(KEY_RIGHT_BRACKET)) value = 1.0f;
        zoom(camera, value, false);
    }
}

void camera::reset(Camera2D& camera) {
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.target = {config::world_width / 2.0f, config::world_height / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

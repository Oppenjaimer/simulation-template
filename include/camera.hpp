#pragma once

#include "raylib.h"

/**
 * @brief Camera control.
 */
namespace camera {
    /**
     * @brief Handle camera controls through mouse/keyboard input.
     * @param camera Camera to modify.
     */
    void update(Camera2D& camera);

    /**
     * @brief Reset camera to its default state.
     * @param camera Camera to reset.
     */
    void reset(Camera2D& camera);
};

#pragma once

#include "raylib.h"

namespace camera {
    // Control camera via mouse/keyboard input
    void update(Camera2D& camera);

    // Reset camera to its default state
    void reset(Camera2D& camera);
};

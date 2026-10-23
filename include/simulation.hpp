#pragma once

#include "state.hpp"

namespace simulation {
    // Update simulation logic
    void update(State& state);

    // Draw simulation components
    void draw(State& state);
}

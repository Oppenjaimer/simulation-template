#pragma once

#include "state.hpp"

/**
 * @brief Simulation logic and render management.
 */
namespace simulation {
    /**
     * @brief Update simulation logic.
     * @param state Current simulation state.
     */
    void update(State& state);

    /**
     * @brief Draw simulation components.
     * @param state Current simulation state.
     */
    void draw(State& state);
}

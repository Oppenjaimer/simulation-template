#pragma once

#include "config.hpp"

struct State {
    bool is_running = true;                             ///< Whether the main loop is active.
    bool is_paused = false;                             ///< Whether the simulation is paused.

    bool settings_collapse = config::settings_collapse; ///< Whether the settings panel is collapsed.
    bool settings_trigger = false;                      ///< Whether a settings panel collapse was triggered.
};

namespace state {
    // Reset state to its default configuration
    void reset(State& state);
}

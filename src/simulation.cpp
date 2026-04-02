#include "simulation.hpp"
#include "state.hpp"
#include "theme.hpp"

void simulation::update(State& state) {
    if (state.is_paused) return;
}

void simulation::draw(State& state) {
    (void)state;

    // World bounds
    DrawRectangleLines(0, 0, config::world_width, config::world_height, theme::bg4);

    // Placeholder circle
    DrawCircle(config::world_width / 2.0f, config::world_height / 2.0f, 10, theme::orange);
}

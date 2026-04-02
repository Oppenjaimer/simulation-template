#include "simulation.hpp"

using namespace simulation;

/**
 * @brief Application entry point.
 * @returns Exit code.
 */
int main() {
    // Initialize global simulation state
    State state;

    // Execute simulation lifecycle
    init(state);
    run(state);
    cleanup(state);

    return 0;
}

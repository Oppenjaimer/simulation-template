#pragma once

namespace utils {
    // Generate random float in range [min, max)
    float get_random_float(float min = 0.0f, float max = 1.0f);

    // Generate random integer in range [min, max]
    int get_random_int(int min, int max);

    // Set raylib resources directory
    bool set_resource_dir(const char* path);
}

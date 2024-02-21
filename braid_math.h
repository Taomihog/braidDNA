#pragma once

#include "braid.h"

struct braid_math {
    // functions for 3d rotation, collision, etc
    static void init_config(braid brd, float sep_surface, float sep_top, float h, float azimu);
    static void rot_out(float * p, size_t ns, float angle); 
    static void rot_in(float * p, size_t ns, size_t ne, float angle); 
    static bool collided(const braid brd, float diameter);
    static size_t alexander_polyn(const braid brd);
    static size_t jones_polyn(const braid brd);
    static float extension(const braid brd);
    static float total_bend(const braid brd);
    static float azimuthal_angle(const braid brd);
    static float polar_angle(const braid brd);
    static float end_distance(const braid brd);
};
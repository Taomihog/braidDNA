#include "braid_math.h"

void braid_math::init_config(braid brd, float sep1, float sep2, float h, float turns) {
    ;
}

void braid_math::rot_out(float * p, size_t ns, float angle) {
    ;
} 

void braid_math::rot_in(float * p, size_t ns, size_t ne, float angle) {
    ;
}

bool braid_math::collided(const braid brd, float diameter) {
    return false;
}

size_t braid_math::alexander_polyn(const braid brd) {
    return 1;
}

size_t braid_math::jones_polyn(const braid brd) {
    return 1;
}

float braid_math::extension(const braid brd) {
    return 1.0;
}

float braid_math::total_bend(const braid brd) {
    return 1.0;
}

float braid_math::azimuthal_angle(const braid brd) {
    return 1.0;
}

float braid_math::polar_angle(const braid brd) {
    return 1.0;
}

float braid_math::end_distance(const braid brd) {
    return 1.0;
}
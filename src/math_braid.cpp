#include "math_braid.h"
#include <iostream>


// Cartesin version, not being used.
// Cartesian math_3d::rotate_along(const Cartesian &v, const Cartesian &u, float alpha) {
//     // u.v
//     float udotv = v.x * u.x + v.y * u.y + v.z * u.z;
//     Cartesian res;
//     res.x = v.x * cos(alpha) + (v.z * u.y - v.y * u.z) * sin(alpha) + u.x * udotv * (1 - cos(alpha));
//     res.y = v.y * cos(alpha) + (v.x * u.z - v.z * u.x) * sin(alpha) + u.y * udotv * (1 - cos(alpha));
//     res.z = v.z * cos(alpha) + (v.y * u.x - v.x * u.y) * sin(alpha) + u.z * udotv * (1 - cos(alpha));
//     return res;
// }

Spherical math_3d::rotate_along(const Spherical& v, const Spherical& u, float alpha) {
    float udotv = sin(v.theta) * sin(u.theta) * cos (v.phi - u.phi) + cos(v.theta) * cos (u.theta);
    
    float xx = sin(v.theta) * cos(v.phi) * cos(alpha) + (cos(v.theta) * sin(u.theta) * sin(u.phi) - sin(v.theta) * sin(v.phi) * cos(u.theta)) * sin(alpha) + sin(u.theta) * cos(u.phi) * udotv * (1 - cos(alpha));
    float yy = sin(v.theta) * sin(v.phi) * cos(alpha) + (sin(v.theta) * cos(v.phi) * cos(u.theta) - cos(v.theta) * sin(u.theta) * cos(u.phi)) * sin(alpha) + sin(u.theta) * sin(u.phi) * udotv * (1 - cos(alpha));
    float zz = cos(v.theta) * cos(alpha) + (sin(v.theta) * sin(v.phi) * sin(u.theta) * cos(u.phi) - sin(v.theta) * cos(v.phi) * sin(u.theta) * sin(u.phi)) * sin(alpha) + cos(u.theta) * udotv * (1 - cos(alpha));
    
    Spherical res;
    res.phi = atan2(yy, xx);
    res.theta = acos(zz);
    return res;
}

void math_3d::rotate_along(float & theta, float & phi, const Spherical &u, float alpha) {
    static float udotv = sin(theta) * sin(u.theta) * cos (phi - u.phi) + cos(theta) * cos (u.theta);
    
    static float xx = sin(theta) * cos(phi) * cos(alpha) + (cos(theta) * sin(u.theta) * sin(u.phi) - sin(theta) * sin(phi) * cos(u.theta)) * sin(alpha) + sin(u.theta) * cos(u.phi) * udotv * (1 - cos(alpha));
    static float yy = sin(theta) * sin(phi) * cos(alpha) + (sin(theta) * cos(phi) * cos(u.theta) - cos(theta) * sin(u.theta) * cos(u.phi)) * sin(alpha) + sin(u.theta) * sin(u.phi) * udotv * (1 - cos(alpha));
    static float zz = cos(theta) * cos(alpha) + (sin(theta) * sin(phi) * sin(u.theta) * cos(u.phi) - sin(theta) * cos(phi) * sin(u.theta) * sin(u.phi)) * sin(alpha) + cos(u.theta) * udotv * (1 - cos(alpha));
    
    phi = atan2(yy, xx);
    theta = acos(zz);

}

size_t math_braid::init_config(braid &brd, float sep1, float sep2, float phi) {
    static const Spherical z {0.0f, 0.0f};
    float polyn = alexander_polyn(brd);
    return polyn;
}

void math_braid::rot_out(Spherical *p, size_t seg, float angle) {
    static const Spherical z {0.0f, 0.0f};
    math_3d::rotate_along(p[seg].theta, p[seg].phi, z, angle);
} 

void math_braid::rot_in(Spherical *p, size_t segs, size_t sege, float angle) {
    float x = 0;
    float y = 0;
    float z = 0;
    for (size_t seg = segs; seg <= sege; ++seg) {
        x += sin(p[seg].theta) * cos(p[seg].phi);
        y += sin(p[seg].theta) * sin(p[seg].phi);
        z += cos(p[seg].theta);
    }
    float r = sqrt(x * x + y * y + z * z);

    static const Spherical axis {acos(z/r), atan2(y, x)};
    for (size_t seg = segs; seg <= sege; ++seg) {
        math_3d::rotate_along(p[seg].theta, p[seg].phi, axis, angle);
    }
}

bool math_braid::collided(const braid &brd, float diameter) {
    return false;
}

size_t math_braid::alexander_polyn(const braid &brd) {
    return 1;
}

size_t math_braid::jones_polyn(const braid &brd) {
    return 1;
}

float math_braid::extension(const braid &brd) {
    return 1.0;
}

float math_braid::total_bend(const braid &brd) {
    return 1.0;
}

float math_braid::azimuthal_angle(const braid &brd) {
    return 1.0;
}

float math_braid::polar_angle(const braid &brd) {
    return 1.0;
}

float math_braid::end_distance(const braid &brd) {
    return 1.0;
}
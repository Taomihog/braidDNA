#pragma once

#include <cmath>

#define EX(theta,phi) (sin(theta) * cos(phi))
#define EY(theta,phi) (sin(theta) * sin(phi))
#define EZ(theta,phi) cos(theta)

#define M_PI       3.14159265358979323846f

#pragma pack(push, 1) 
// struct Cartesian {
//     float x;
//     float y;
//     float z;
// };
struct Spherical {
    float theta; // polar
    float phi; // azimuthal
};
#pragma pack(pop) 

struct braid {

    braid() = delete;

    braid(size_t n): n_seg(n) {
        polymer[0] = new Spherical [n_seg];
        polymer[1] = new Spherical [n_seg];
    }

    ~braid() {
        delete[] polymer[0];
        delete[] polymer[1];
    }

    static void copy(braid & b_dest, const braid & b_src, size_t chain, size_t seg_start, size_t seg_end) {
        // copy the element in a close interval [seg_start, seg_end]
        // has to make sure seg_start <= seg_end
        const size_t sz = sizeof(Spherical);
        memcpy(b_dest.polymer[chain] + sz * seg_start, b_src.polymer[chain] + sz * seg_start, sz * (seg_end - seg_start + 1));
    }

    size_t n_seg;
    Spherical * polymer[2];
};

class math_3d {
public:
    // rotate vector v along another vector u by angle alpha in right-handed coordinate
    // static Cartesian rotate_along(const Cartesian &v, const Cartesian &u, float alpha);
    static Spherical rotate_along(const Spherical &v, const Spherical &u, float alpha);
    static void rotate_along(float &theta, float &phi, const Spherical &u, float alpha);
};

struct math_braid {
    // functions for 3d rotation, collision, etc
    static size_t init_config(braid &brd, float sep_surface, float sep_top, float phi);
    static void rot_out(Spherical *p, size_t n,float angle); 
    static void rot_in(Spherical *p, size_t ns, size_t ne, float angle); 
    static bool collided(const braid &brd, float diameter);
    static size_t alexander_polyn(const braid &brd);
    static size_t jones_polyn(const braid &brd);
    static float extension(const braid &brd);
    static float total_bend(const braid &brd);
    static float azimuthal_angle(const braid &brd);
    static float polar_angle(const braid &brd);
    static float end_distance(const braid &brd);
};
#pragma once

#define x(i) (3 * (i))
#define y(i) (3 * (i) + 1)
#define z(i) (3 * (i) + 2)

struct braid {

    braid(size_t n): n_seg(n) {
        polymer[0] = new float [n_seg * 3];
        polymer[1] = new float [n_seg * 3];
    }

    ~braid() {
        delete[] polymer[0];
        delete[] polymer[1];
    }

    size_t n_seg;
    float * polymer[2];
};
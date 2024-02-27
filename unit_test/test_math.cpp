#include <stdio.h>
#include <cmath>
#include "math_braid.h"

#define DEG(rad) ((rad) * 57.295779513082320876f)

void print_test_rot(Spherical v,Spherical u, float alpha) {
    printf("v = (%.0f, %.0f), ", DEG(v.theta), DEG(v.phi));
    printf("u = (%.0f, %.0f), ", DEG(u.theta), DEG(u.phi));
    Spherical v2 = math_3d::rotate_along(v, u, alpha);
    printf("rot by %.0f\t-> (%.0f, %.0f).\n", DEG(alpha), DEG(v2.theta), DEG(v2.phi));
}
void test_rotation() {
    printf("1. Test 3D rotation\n");
    Spherical v {M_PI/6.0f, M_PI/4.0f};
    Spherical u {0,0};
    print_test_rot(v, u, M_PI/4.0f);
    print_test_rot(v, u, M_PI/2.0f);
    print_test_rot(v, u, M_PI);
    print_test_rot(v, u, 1.5 * M_PI);
    math_3d::rotate_along(v.theta, v.phi, u, 1.5 * M_PI);
    printf("further test, rot by %.0f\t-> (%.0f, %.0f).\n", DEG(1.5 * M_PI), DEG(v.theta), DEG(v.phi));
    printf("\n");

    v = {M_PI/6.0f, M_PI/4.0f};
    u = {M_PI/2.0f, 0.0f};
    print_test_rot(v, u,  M_PI);
    print_test_rot(v, u, -M_PI);
    print_test_rot(v, u, asin(1.0f/sqrt(7.0f)));
    print_test_rot(v, u, 2.0f * asin(1.0f/sqrt(7.0f)));
    printf("\n");

    u = {M_PI/2.0f, M_PI/2.0f};
    print_test_rot(v, u,  M_PI);
    print_test_rot(v, u, -M_PI);
    print_test_rot(v, u, -asin(1.0f/sqrt(7.0f)));
    print_test_rot(v, u, -2.0f * asin(1/sqrt(7.0f)));
    print_test_rot(v, u, acos(1/sqrt(7.0f)));
    printf("\n");

    u = {M_PI/2.0f, M_PI/4.0f};
    print_test_rot(v, u, M_PI);
    printf("\n");
}

int main() {
    // test the math
    printf("Test Math Library\n");
    test_rotation();

    return 0;
}
/*****************************************************************************************************
    Monte-Carlo simulation of the torque to braid 2 DNA molecules.
    
    note:
    Vologodskii's simulation is earlier than the invention of Jone's polynomial. 
    A goal of this program is to explore the possibility to use Jones polynomial to replace Alexander polynomial to speed up the simulation.

    reference:
    A. Vologodskii and V. Rybenkov. 2009. Simuation of DNA catenanes, 2009 Phys Chem Chem Phys.
    A. Vologodskii, A. Lukashin, and M. Frank-KamenetskiT. 1975. Topological Interaction Between Polymer Chains, 1975. Sov Phys -JETP.
    A. Vologodskii, A. Lukashin, M. Frank-Kamenetskii, and V. Anshelevich. 1973. The Topological Problem in Statistical Mechanics of Polymer Chains. Sov Phys -JETP.
    G. Charvin, A. Vologodskii, D. Bensimon, and V. Croquette. 2005. Braiding DNA: Experiments, Simulations and Models. Biophy J. 
****************************************************************************************************/


// create a c program, then convert it slowly to cuda 

#include <iostream>
#include <random>
#include <cmath>

#include "angle_adjust.h"
#include "math_braid.h"


int main(int argc, char ** argv) {

    // unit: pN, nm, s, rad
    // *******************constant definitions and memory allocation**********************
    // DNA parameters:
    constexpr float kT = 4.1f;
    constexpr float alpha = 2.4f;
    constexpr float polymer_diameter = 2.0f;
    constexpr size_t n_segments = 10000;
    constexpr float total_length = 4300.0f;
    constexpr float segment_length = total_length / n_segments;

    // DNA anchoring positions and linking number of the braid
    constexpr float separation_top = 500.0f;
    constexpr float separation_surface = 300.0f;
    constexpr float LK = 5.0f;
    constexpr float init_azimuthal_angle = 2.0f * M_PI * LK;

    // trap stiffness along 3 directions and the constant force
    constexpr float k_azimu = 0.1f;
    constexpr float k_polar = 0.1f;
    constexpr float k_r = 1.0f;
    constexpr float force = 0.5f;

    // simulation parameters;
    constexpr size_t max_steps = 10000;
    constexpr float init_angle = 0.1f;
    angle_adjust angle(init_angle, 1000);

    // struct for polymer coordinates
    braid b_curr(n_segments);
    braid b_temp(n_segments);
    constexpr size_t polymer_bytes = n_segments * 3 * sizeof(float);

    // initialize the corrdinates
    math_braid::init_config(b_curr, separation_surface, separation_top, init_azimuthal_angle);
    // cannot guarantee the 2 arrays are allocated in contiguous memory, have to copy them individually
    memcpy(b_temp.polymer[0], b_curr.polymer[0], polymer_bytes);
    memcpy(b_temp.polymer[1], b_curr.polymer[1], polymer_bytes);

    // Seed the random number engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random boolean variable
    std::bernoulli_distribution rnd_type_of_rot(0.1); // only 10% chance to do rot_out()
    // std::uniform_int_distribution<size_t> rnd_node(0, n_segments); // there are n_seg + 1 nodes
    std::uniform_int_distribution<size_t> rnd_seg(0, n_segments - 1); // there are n_seg segments
    std::uniform_int_distribution<size_t> rnd_chain(0, 2); // 50% chance of Chain1 and Chain2
    std::uniform_real_distribution<float> rnd_cos(-1,1);
    std::uniform_real_distribution<float> rnd_p(0,1);
    //std::bernoulli_distribution rnd_chain(0.5); 


    // ****************************thermalization + simulation****************************
    // variables for move
    size_t chain; // 0 = move the first chain, 1 = move the second chain
    size_t seg_start, seg_end; // start and end node numbers for move
    size_t i_start, i_end;
    size_t size_to_copy;

    // variables for acceptable check
    bool is_succeeded = false;
    float e_total = 0.0f;
    float e_prev = 1e10f;
    bool rotation_type = false;

    for (size_t step = 0; step < max_steps; ++step) {
        //pick a type of move
        rotation_type = rnd_type_of_rot(gen);
        chain = rnd_chain(gen);
        seg_start = rnd_seg(gen);

        if (rotation_type) {
            // rotate1
            braid::copy(b_temp, b_curr, chain, seg_start, seg_start);
            math_braid::rot_out(b_temp.polymer[chain], seg_start, std::acos(rnd_cos(gen)));
        } else {
            //pick 2 segment 
            
            seg_end = seg_start;
            while(seg_start == seg_end) {
                seg_end = rnd_seg(gen);
            }
            seg_start = std::min(seg_end, seg_start);
            seg_end = std::max(seg_end, seg_start);
            // rotate2
            braid::copy(b_temp, b_curr, chain, seg_start, seg_end);
            math_braid::rot_in(b_temp.polymer[chain], seg_start, seg_end, angle());
        }



        // calculate if collide, p1
        is_succeeded = math_braid::collided(b_temp, polymer_diameter) && 

        // calculate alexandra polynomial, p2
        math_braid::alexander_polyn(b_temp) == 0;

        // calculate the energy, p3
        // energy equals to E_polymer + E_trap - Fz
        if (is_succeeded) {
            e_total = alpha * math_braid::total_bend(b_temp) + 
                    0.5 * k_azimu * (float)std::pow(math_braid::azimuthal_angle(b_temp) - init_azimuthal_angle, 2) + 
                    0.5 * k_polar * (float)std::pow(math_braid::polar_angle(b_temp), 2) +
                    0.5 * k_r * (float)std::pow(math_braid::end_distance(b_temp) - separation_top, 2) -
                    force * math_braid::extension(b_temp);
            
            if (std::exp(-(e_total - e_prev)/kT) > rnd_p(gen)) {
                //memcpy
                e_total = e_prev;
                rotation_type ? braid::copy(b_curr, b_temp, chain, seg_start, seg_start): 
                                braid::copy(b_curr, b_temp, chain, seg_start, seg_end);
            } else {
                is_succeeded = false;
            }
        }


        // calculate the failure rate and reduce/increase the step size by an average of failure rate over many steps.
        angle.update(is_succeeded);
     }
    
    return 0;
}
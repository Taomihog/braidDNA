#pragma once

#include <iostream>
class angle_adjust {
public:
    angle_adjust(float init_angle, int length = 1000): angle_curr(init_angle), history_length(length) {
        if (length == 0) [[unlikely]] {
            std::cerr << "length in angle_adjust can't be zero.\n";
            history_length = 1000;
        }

        successes = new bool[history_length];

        for (size_t i = 0; i < history_length; ++i) {
            successes[i] = 0;
        }
    }

    ~angle_adjust() {
        delete[] successes;
    }

    float operator()() const;
    void update(bool);
    float success_rate() const;
    
private:
    bool * successes;
    float angle_curr;
    size_t history_length;
    size_t n_updated = 0;
    size_t last_record = 0;
    static const float pgain; 
};

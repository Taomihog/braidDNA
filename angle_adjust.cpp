#pragma once

#include "angle_adjust.h"

const float angle_adjust:: pgain = 0.01;

float angle_adjust::operator()() const {
    return angle_curr;
};

void angle_adjust::update(bool b) {
    ++ n_updated;
    successes[last_record] = b;

    ++last_record;
    if (last_record >= history_length) [[unlikely]] {
        last_record = 0;
    }

    angle_curr = angle_curr  + (success_rate() - 0.25) * pgain;
}

float angle_adjust::success_rate() const {
    if (n_updated < history_length) [[unlikely]] {
        return 0.25;
    }

    int rate = 0;
    for (size_t i = 0; i < history_length; ++i) {
        if (successes[i] == 1) {
            ++ rate;
        }
    }
    return ((float) rate) / std::min(history_length, n_updated);
}
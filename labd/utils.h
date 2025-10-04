#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>
#include <map>
#include <string>

template<typename T>
double expected_value(T& dice, unsigned number_of_rolls = 1000) {
    auto accum = 0lu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += dice.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

template<typename T>
double value_probability(unsigned value, T& dice, unsigned number_of_rolls = 1000) {
    unsigned count = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        if (dice.roll() == value) {
            ++count;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

template<typename T>
std::map<unsigned, double> build_histogram(T& dice, unsigned number_of_rolls = 1000) {
    std::map<unsigned, unsigned> counts;

    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        unsigned value = dice.roll();
        counts[value]++;
    }

    std::map<unsigned, double> histogram;
    for (const auto& pair : counts) {
        histogram[pair.first] = static_cast<double>(pair.second) / number_of_rolls;
    }

    return histogram;
}

inline void print_histogram(const std::map<unsigned, double>& histogram, unsigned max_bars = 50) {
    if (histogram.empty()) return;

    double max_prob = 0;
    for (const auto& pair : histogram) {
        if (pair.second > max_prob) max_prob = pair.second;
    }

    for (const auto& pair : histogram) {
        unsigned bar_length = static_cast<unsigned>((pair.second / max_prob) * max_bars);
        std::cout << std::setw(3) << pair.first << ": "
            << std::string(bar_length, '*')
            << " (" << std::fixed << std::setprecision(2) << pair.second * 100 << "%)" << std::endl;
    }
    std::cout << std::endl;
}

#endif
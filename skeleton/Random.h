#pragma once
#include <random>
#include <cmath>

namespace Random {

    inline std::mt19937& Generator() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    inline float Normal(float media, float varianza) {
        std::normal_distribution<float> dist(media, std::sqrt(varianza));
        return dist(Generator());
    }

    inline float Uniform(float min, float max) {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        return dist(Generator());
    }

}
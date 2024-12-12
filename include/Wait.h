#ifndef WAIT_H
#define WAIT_H

#include <random>
#include <chrono>
#include <thread>

class Wait {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

public:
    Wait(int seed, int min, int max);
    void wait();
};

#endif // WAIT_H
#include "Wait.h"

Wait::Wait(int seed, int min, int max) : rng(seed), dist(min, max) {}

void Wait::wait() {
    std::this_thread::sleep_for(std::chrono::seconds(dist(rng)));
}
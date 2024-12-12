#include "Semaphore.h"
#include <iostream>

Semaphore::Semaphore(int count) : count(count) {}

void Semaphore::notify(std::string event) {
    std::unique_lock<std::mutex> lock(mutex);
    count++;
    // std::cout << "Notified "<< event << count << std::endl;
    condition.notify_one();
}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mutex);
    while (count == 0) {
        condition.wait(lock);
    }
    count--;
}
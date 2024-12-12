#pragma once
#include "Semaphore.h"
#include <string>
#include <mutex>
#include <atomic>
#include <SFML/Graphics.hpp>

class Customer
{
public:
    Customer();
    Customer(int id, Semaphore &semaphoreWaitingCustomer, Semaphore &semaphoreWaitingOrder, std::string* state, std::mutex* mutex);
    void run();
    void stop();
    void update(sf::CircleShape &customerShape);

private:
    int id;
    Semaphore *semaphoreWaitingCustomer;
    Semaphore *semaphoreWaitingOrder;
    std::string* statePtr;
    std::mutex* mutexPtr;
    std::atomic<bool> running{true};
};
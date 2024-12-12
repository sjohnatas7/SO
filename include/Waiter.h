
#ifndef WAITER_H
#define WAITER_H

#include "Semaphore.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <mutex>

class Waiter {
public:
    Waiter () = default;
    Waiter(int id);
    Waiter(int id, Semaphore& semaphoreWaitingCustomer, Semaphore& semaphoreWaitingOrder, Semaphore& semaphoreOrderReady, Semaphore& semaphoreOrderPrepared);
    void setStatePtr(std::string* state, std::mutex* mutex);
    void run();
    void update(sf::CircleShape &waiterShape);
    void stop();
private:
    int id;
    Semaphore* semaphoreWaitingCustomer;
    Semaphore* semaphoreWaitingOrder;
    Semaphore* semaphoreOrderReady;
    Semaphore* semaphoreOrderPrepared;
    std::string* statePtr;
    std::mutex* mutexPtr;
    bool running = true;
};

#endif // WAITER_H
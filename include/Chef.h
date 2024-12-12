
#ifndef CHEF_H
#define CHEF_H

#include "Semaphore.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <mutex>

class Chef {
public:
    Chef(Semaphore& semaphoreOrderReady, Semaphore& semaphoreOrderPrepared);
    void setStatePtr(std::string* state, std::mutex* mutex);
    void run();
    void update(sf::CircleShape &chefShape);
    int getCookingTime();
    void setCookingTime(int time);
    void stop();

private:
    Semaphore* semaphoreOrderReady;
    Semaphore* semaphoreOrderPrepared;
    std::string* statePtr;
    std::mutex* mutexPtr;
    int cookingTime = 1;
    bool running = true;
};

#endif // CHEF_H
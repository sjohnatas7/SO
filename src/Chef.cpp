#include "Chef.h"
#include "Wait.h"
#include <iostream>

Chef::Chef(Semaphore& semaphoreOrderReady, Semaphore& semaphoreOrderPrepared)
    : semaphoreOrderReady(&semaphoreOrderReady), semaphoreOrderPrepared(&semaphoreOrderPrepared) {}

void Chef::setStatePtr(std::string* state, std::mutex* mutex) {
    statePtr = state;
    mutexPtr = mutex;
}

void Chef::run() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Waiting";
        }
        std::cout << "Chef is waiting for an order" << std::endl;
        semaphoreOrderReady->wait();

        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Preparing";
        }
        std::cout << "Chef is preparing the order" << std::endl;
        Wait(1,1,2).wait();

        std::cout << "Chef has finished preparing the order" << std::endl;
        semaphoreOrderPrepared->notify("Order prepared ");

    }
}

void Chef::stop() {
    running = false;
    // Notify semaphore in case chef is waiting
    semaphoreOrderReady->notify("Chef stopped ");
}

void Chef::update(sf::CircleShape &chefShape) {
    // Update chef color based on state
    if (*statePtr == "Waiting") {
        chefShape.setFillColor(sf::Color::Red);
    } else if (*statePtr == "Preparing") {
        chefShape.setFillColor(sf::Color::Yellow);
    }
}

int Chef::getCookingTime() {
    return cookingTime;
}

void Chef::setCookingTime(int time) {
    if (time < 1) {
        time = 1;
        return;
    }
    cookingTime = time;
}
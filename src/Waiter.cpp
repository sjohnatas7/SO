#include "Waiter.h"
#include "Wait.h"
#include <iostream>
#include <thread>
#include <chrono>

// Waiter::Waiter() : id(nullptr), semaphoreWaitingCustomer(nullptr), semaphoreWaitingOrder(nullptr) {}

Waiter::Waiter(int id) : id(id), semaphoreWaitingCustomer(nullptr), semaphoreWaitingOrder(nullptr) {}

Waiter::Waiter(int id, Semaphore& semaphoreWaitingCustomer, Semaphore& semaphoreWaitingOrder, Semaphore& semaphoreOrderReady, Semaphore& semaphoreOrderPrepared)
    : id(id), semaphoreWaitingCustomer(&semaphoreWaitingCustomer), semaphoreWaitingOrder(&semaphoreWaitingOrder), 
      semaphoreOrderReady(&semaphoreOrderReady), semaphoreOrderPrepared(&semaphoreOrderPrepared) {}

void Waiter::setStatePtr(std::string* state, std::mutex* mutex) {
    statePtr = state;
    mutexPtr = mutex;
}

void Waiter::run() {
    while (running) {
        // Update state to "Waiting"
        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Waiting";
        }
        std::cout << "Waiter " << id << " is waiting for a customer" << std::endl;
        semaphoreWaitingCustomer->wait();

        // Update state to "Attending"
        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Attending";
        }
        std::cout << "Waiter " << id << " is attending" << std::endl;
        Wait(1, 1, 5).wait();

        // Pass the order to the chef
        semaphoreOrderReady->notify("Order ready ");
        std::cout << "Waiter " << id << " has passed the order to the chef" << std::endl;

        // Wait for the chef to prepare the order
        semaphoreOrderPrepared->wait();

        // Deliver the order to the customer
        semaphoreWaitingOrder->notify("Order delivered ");
        std::cout << "Waiter " << id << " has delivered the order" << std::endl;

    }
}

void Waiter::stop() {
    running = false;
    // Notify semaphore in case waiter is waiting
    semaphoreWaitingCustomer->notify("Waiter stopped ");
}

void Waiter::update(sf::CircleShape &waiterShape) {
    // Update waiter color based on state
    if (*statePtr == "Waiting") {
        waiterShape.setFillColor(sf::Color::White);
    } else if (*statePtr == "Attending") {
        waiterShape.setFillColor(sf::Color::Green);
    }
}
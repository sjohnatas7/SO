#include "Customer.h"
#include "Wait.h"
#include <iostream>

Customer::Customer()
    : id(0),
      semaphoreWaitingCustomer(nullptr),
      semaphoreWaitingOrder(nullptr),
      statePtr(nullptr),
      mutexPtr(nullptr),
      running(true) {}

Customer::Customer(int id, Semaphore &semaphoreWaitingCustomer, Semaphore &semaphoreWaitingOrder, std::string* state, std::mutex* mutex)
    : id(id),
      semaphoreWaitingCustomer(&semaphoreWaitingCustomer),
      semaphoreWaitingOrder(&semaphoreWaitingOrder),
      statePtr(state),
      mutexPtr(mutex),
      running(true) {}

void Customer::run()
{
    while (running)
    {
        // Update state to "Waiting"
        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Waiting";
        }
        std::cout << "Customer " << id << " has arrived" << std::endl;
        semaphoreWaitingCustomer->notify("Customer arrived ");
        semaphoreWaitingOrder->wait();
        // Update state to "Eating"
        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Eating";
            std::cout << "Customer " << id << " is eating" << std::endl;
        }
        std::cout << "Customer " << id << " has received the order" << std::endl;
        Wait(1, 1, 5).wait();

        {
            std::lock_guard<std::mutex> lock(*mutexPtr);
            *statePtr = "Idle";
            std::cout << "Customer " << id << "is idle" << std::endl;
        }
        Wait(1, 1, 7).wait();
    }
}

void Customer::stop() {
    running = false;
}

void Customer::update(sf::CircleShape &customerShape) {
    // Update customer color based on state

    if (*statePtr == "Waiting") {
        customerShape.setFillColor(sf::Color(100,100,100)); // Changed from Red to Blue
    } else if (*statePtr == "Eating") {
        customerShape.setFillColor(sf::Color::Yellow);
    } else {
        customerShape.setFillColor(sf::Color::Red); // Changed from Blue to Red
    }
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "Semaphore.h"
#include "Waiter.h"
#include "Chef.h"
#include "Customer.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void increaseCustomers();
    void decreaseCustomers();
    void increaseCookingTime();
    void decreaseCookingTime();

    sf::RenderWindow window;
    std::vector<sf::CircleShape> customerShapes;
    sf::CircleShape chefShape;
    sf::CircleShape waiterShape1;
    sf::CircleShape waiterShape2;

    std::vector<std::unique_ptr<Customer>> customers;
    std::vector<std::thread> customerThreads;
    std::vector<std::string> customerStates;
    std::vector<std::string> waiterStates;
    std::string chefState;

    Semaphore semaphoreWaitingCustomer;
    Semaphore semaphoreWaitingOrder;
    Semaphore semaphoreOrderReady;
    Semaphore semaphoreOrderPrepared;

    Waiter waiter1;
    Waiter waiter2;
    Chef chef;

    int numCustomers;
    std::mutex mutex;

    std::thread waiterThread1;
    std::thread waiterThread2;
    std::thread chefThread;

    sf::Text cookingTimeText; 
    sf::Font font;            
};
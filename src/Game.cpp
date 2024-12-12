#include "Game.h"
#include "Semaphore.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Restaurante"),
               semaphoreWaitingCustomer(0),
               semaphoreWaitingOrder(0),
               semaphoreOrderReady(0),
               semaphoreOrderPrepared(0),
               waiter1(1, semaphoreWaitingCustomer, semaphoreWaitingOrder, semaphoreOrderReady, semaphoreOrderPrepared),
               waiter2(2, semaphoreWaitingCustomer, semaphoreWaitingOrder, semaphoreOrderReady, semaphoreOrderPrepared),
               chef(semaphoreOrderReady, semaphoreOrderPrepared),
               numCustomers(5) // Initialize numCustomers
{
    // Visual representations initialization
    chefShape = sf::CircleShape(30);
    chefShape.setFillColor(sf::Color::Red);
    chefShape.setPosition(100, 100);

    waiterShape1 = sf::CircleShape(30);
    waiterShape1.setFillColor(sf::Color::Green);
    waiterShape1.setPosition(300, 100);

    waiterShape2 = sf::CircleShape(30);
    waiterShape2.setFillColor(sf::Color::Green);
    waiterShape2.setPosition(500, 100);

    for (int i = 0; i < numCustomers; ++i)
    {
        sf::CircleShape customerShape(20);
        customerShape.setFillColor(sf::Color::Blue);
        customerShape.setPosition(100 + i * 150, 300);
        customerShape.setPosition(100 + i * 150, 300);
        customerShapes.push_back(customerShape);
    }

    // Initialize states
    chefState = "Waiting";
    waiterStates = std::vector<std::string>(2, "Waiting");
    customerStates = std::vector<std::string>(numCustomers, "Waiting");

    // Set state pointers
    waiter1.setStatePtr(&waiterStates[0], &mutex);
    waiter2.setStatePtr(&waiterStates[1], &mutex);
    chef.setStatePtr(&chefState, &mutex);

    // Initialize customerStates
    customerStates.resize(numCustomers, "Idle");

    // Initialize customers and start threads
    for (int i = 0; i < numCustomers; ++i)
    {
        customers.emplace_back(std::make_unique<Customer>(i, semaphoreWaitingCustomer, semaphoreWaitingOrder, &customerStates[i], &mutex));
        customerThreads.emplace_back(&Customer::run, customers.back().get());
    }

    waiterThread1 = std::thread(&Waiter::run, &waiter1);
    waiterThread2 = std::thread(&Waiter::run, &waiter2);
    chefThread = std::thread(&Chef::run, &chef);

    // Load a font
    if (!font.loadFromFile("./assets/arial.ttf"))
    {
        // Handle error
        std::cerr << "Failed to load font 'Arial.ttf'. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    // Initialize cookingTimeText
    cookingTimeText.setFont(font);
    cookingTimeText.setCharacterSize(24);
    cookingTimeText.setFillColor(sf::Color::White);
    cookingTimeText.setPosition(10, 10);
}

Game::~Game()
{
    // No need to join threads here, as the game loop runs in the main thread

    // Stop all customers
    for (auto &customer : customers)
    {
        customer->stop();
    }

    // Stop waiters and chef
    waiter1.stop();
    waiter2.stop();
    chef.stop();

    // Join customer threads
    for (auto &thread : customerThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    // Join waiter threads
    if (waiterThread1.joinable())
    {
        waiterThread1.join();
    }
    if (waiterThread2.joinable())
    {
        waiterThread2.join();
    }

    // Join chef thread
    if (chefThread.joinable())
    {
        chefThread.join();
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                increaseCustomers();
                break;
            case sf::Keyboard::Down:
                decreaseCustomers();
                break;
            case sf::Keyboard::Right:
                increaseCookingTime();
                break;
            case sf::Keyboard::Left:
                decreaseCookingTime();
                break;
            default:
                break;
            }
        }
    }
}

void Game::update()
{
    waiter1.update(waiterShape1);
    waiter2.update(waiterShape2);
    chef.update(chefShape);

    for (int i = 0; i < numCustomers; ++i)
    {
        customers[i]->update(customerShapes[i]);
    }

    // Update cooking time text
    // cookingTimeText.setString("Cooking Time: " + std::to_string(chef.getCookingTime()));
}

void Game::render()
{
    window.clear();

    // Draw chef
    window.draw(chefShape);
    // Draw waiters
    window.draw(waiterShape1);
    window.draw(waiterShape2);
    // Draw customers
    for (int i = 0; i < numCustomers; ++i)
    {
        window.draw(customerShapes[i]);
    }

    // window.draw(cookingTimeText);

    window.display();
}

void Game::increaseCustomers()
{
    numCustomers++;

    // Add new state for the customer
    customerStates.push_back("Idle");

    // Create new graphical representation
    sf::CircleShape customerShape(20);
    customerShape.setFillColor(sf::Color::Blue);
    customerShape.setPosition(100 + (numCustomers - 1) * 150, 300);
    customerShapes.push_back(customerShape);

    // Add new customer and start thread
    customers.emplace_back(std::make_unique<Customer>(numCustomers - 1, semaphoreWaitingCustomer, semaphoreWaitingOrder, &customerStates.back(), &mutex));
    customerThreads.emplace_back(&Customer::run, customers.back().get());
}

void Game::decreaseCustomers()
{
    if (numCustomers > 0)
    {
        numCustomers--;

        // Stop the last customer
        customers.back()->stop();

        // Join the customer thread
        if (customerThreads.back().joinable())
        {
            customerThreads.back().join();
        }

        // Remove customer data
        customers.pop_back();
        customerThreads.pop_back();
        customerStates.pop_back();
        customerShapes.pop_back();
    }
}

void Game::increaseCookingTime()
{
    int time = chef.getCookingTime();
    time++;
    chef.setCookingTime(time);
}

void Game::decreaseCookingTime()
{
    int time = chef.getCookingTime();
    time--;
    chef.setCookingTime(time);
}
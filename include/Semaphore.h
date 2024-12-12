#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0);
    void notify(std::string event);
    void wait();

private:
    std::mutex mutex;
    std::condition_variable condition;
    int count;
};;

#endif // SEMAPHORE_H
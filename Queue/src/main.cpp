#include "../headers/queue.h"
#include "iostream"

int main() {
    g3::queue<int> intQueue;

    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);
    intQueue.push(40);

    std::cout << "Front element: " << intQueue.front() << std::endl;
    std::cout << "Back element: " << intQueue.back() << std::endl;

    intQueue.pop();

    std::cout << "Front element after popping: " << intQueue.front() << std::endl;
    std::cout << "Back element after popping: " << intQueue.back() << std::endl;

    if (intQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    std::cout << "Size of the queue: " << intQueue.size() << std::endl;

    g3::queue<int> anotherQueue;
    anotherQueue = intQueue;

    std::cout << "Front element of the newly assigned queue: " << anotherQueue.front() << std::endl;
    std::cout << "Back element of the newly assigned queue: " << anotherQueue.back() << std::endl;

    return 0;
}
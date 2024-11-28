#include <iostream>
#include <vector>

class Semaphore {
private:
    int count;  // Count of available resources

public:
    // Constructor to initialize the semaphore with an initial count
    Semaphore(int initial_count) : count(initial_count) {}

    // Delete the copy constructor and copy assignment operator to avoid copying semaphores
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    // Allow move constructor
    Semaphore(Semaphore&& other) noexcept : count(other.count) {}

    // Allow move assignment operator
    Semaphore& operator=(Semaphore&& other) noexcept {
        if (this != &other) {
            count = other.count;
        }
        return *this;
    }

    // Wait (decrement) operation
    void wait() {
        while (count <= 0) {
            // Busy-wait: spin-lock
        }
        --count;
    }

    // Signal (increment) operation
    void signal() {
        ++count;
    }

    // Method to get the current count (for demonstration purposes)
    int getCount() const {
        return count;
    }
};

// Function to simulate some work by threads (for example)
void work(Semaphore& sem) {
    sem.wait();  // Wait for the semaphore
    std::cout << "Working on a task, current semaphore count: " << sem.getCount() << std::endl;
    sem.signal();  // Signal completion of the task
}

int main() {
    Semaphore sem(2);  // Initial count of 2

    // Simulate multiple tasks (threads or processes)
    work(sem);
    work(sem);
    work(sem);

    return 0;
}

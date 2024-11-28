#include <iostream>
#include <cstdlib>
class Semaphore {
private:
    int count;  // Semaphore count for available resources

public:
    // Constructor to initialize the semaphore with an initial count
    Semaphore(int initial_count) : count(initial_count) {}

    // Delete the copy constructor and copy assignment operator to avoid copying semaphores
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    // Wait (decrement) operation
    void wait() {
        while (count <= 0) {
            // Busy-wait: spin-lock (simulated by while loop)
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

class DiningPhilosopher {
private:
    int id;
    Semaphore& leftFork;
    Semaphore& rightFork;

public:
    DiningPhilosopher(int id, Semaphore& leftFork, Semaphore& rightFork)
        : id(id), leftFork(leftFork), rightFork(rightFork) {}

    void dine() {

        think();
        pickUpForks();
        eat();
        putDownForks();
    }

private:
    void think() {
        std::cout << "Philosopher " << id << " is thinking.\n";
    }

    void pickUpForks() {
        std::cout << "Philosopher " << id << " is trying to pick up forks.\n";
        leftFork.wait();
        rightFork.wait();
    }

    void eat() {
        std::cout << "Philosopher " << id << " is eating.\n";
    }

    void putDownForks() {
        std::cout << "Philosopher " << id << " is putting down forks.\n";
        leftFork.signal();
        rightFork.signal();
    }
};

int main() {
    // Create semaphores for each fork
    Semaphore fork0(1);
    Semaphore fork1(1);
    Semaphore fork2(1);
    Semaphore fork3(1);
    Semaphore fork4(1);

    // Create philosophers and simulate their actions sequentially (no threads used)
    DiningPhilosopher philosopher0(0, fork0, fork1);
    DiningPhilosopher philosopher1(1, fork1, fork2);
    DiningPhilosopher philosopher2(2, fork2, fork3);
    DiningPhilosopher philosopher3(3, fork3, fork4);
    DiningPhilosopher philosopher4(4, fork4, fork0);

    // Simulate the dining process
    philosopher0.dine();
    philosopher1.dine();
    philosopher2.dine();
    philosopher3.dine();
    philosopher4.dine();

    return 0;

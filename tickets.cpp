#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

int tickets = 10; // Semaphore: total number of tickets
bool isCounterAvailable = true; // Mutex simulation
int timeUnits = 0; // Time counter for simulating real-time

void bookTicket(int customerId) {
    while (true) {
        // Simulate checking the counter availability
        if (isCounterAvailable && tickets > 0) {
            isCounterAvailable = false; // Lock the counter

            // Simulate the booking process
            std::cout << "Customer " << customerId << " is booking a ticket...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            tickets--;
            std::cout << "Customer " << customerId << " booked a ticket. "
                      << tickets << " tickets remaining.\n";

            isCounterAvailable = true; // Unlock the counter
            return;
        }

        // If no tickets are left
        if (tickets == 0) {
            std::cout << "Customer " << customerId << " found no tickets available.\n";
            return;
        }
    }
}

int main() {
    std::srand(std::time(nullptr));

    int totalCustomers = 15; // Number of simulated customers

    for (int i = 1; i <= totalCustomers; ++i) {
        // Simulate customer arrival at random intervals
        int arrivalTime = std::rand() % 3 + 1; // Random wait between 1-3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(arrivalTime));

        std::cout << "Customer " << i << " has arrived at time unit " << timeUnits << ".\n";
        timeUnits += arrivalTime;

        bookTicket(i);
    }

    std::cout << "Simulation complete. Tickets sold out.\n";
    return 0;
}


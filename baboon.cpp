#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

const int MAX_ON_ROPE = 5; // Maximum number of baboons on the rope
int baboons_on_rope = 0;   // Current number of baboons on the rope
int rope_direction = 0;    // 0 = no direction, 1 = left to right, -1 = right to left

// Simulating a mutex using a basic lock mechanism
bool is_locked = false;    // Mutex-like lock

void lock() {
    while (is_locked) {
        // Simulate waiting for the lock
        for (int i = 0; i < 1000000; ++i); // Busy-wait loop
    }
    is_locked = true;
}

void unlock() {
    is_locked = false;
}

// Simulate a baboon crossing from left to right
void left_baboon_cross(int id) {
    lock();
    if (rope_direction == 0 || rope_direction == 1) {
        if (baboons_on_rope < MAX_ON_ROPE) {
            rope_direction = 1; // Set rope direction to left-to-right
            ++baboons_on_rope;
            std::cout << "Left baboon " << id << " is crossing. Baboons on rope: " << baboons_on_rope << std::endl;
            unlock();
            for (int i = 0; i < 1000000; ++i); // Simulate crossing time
            lock();
            --baboons_on_rope;
            std::cout << "Left baboon " << id << " has crossed. Baboons on rope: " << baboons_on_rope << std::endl;
            if (baboons_on_rope == 0) rope_direction = 0; // Reset direction if rope is empty
        } else {
            std::cout << "Left baboon " << id << " is waiting. Rope is full." << std::endl;
        }
    } else {
        std::cout << "Left baboon " << id << " is waiting. Rope busy in other direction." << std::endl;
    }
    unlock();
}

// Simulate a baboon crossing from right to left
void right_baboon_cross(int id) {
    lock();
    if (rope_direction == 0 || rope_direction == -1) {
        if (baboons_on_rope < MAX_ON_ROPE) {
            rope_direction = -1; // Set rope direction to right-to-left
            ++baboons_on_rope;
            std::cout << "Right baboon " << id << " is crossing. Baboons on rope: " << baboons_on_rope << std::endl;
            unlock();
            for (int i = 0; i < 1000000; ++i); // Simulate crossing time
            lock();
            --baboons_on_rope;
            std::cout << "Right baboon " << id << " has crossed. Baboons on rope: " << baboons_on_rope << std::endl;
            if (baboons_on_rope == 0) rope_direction = 0; // Reset direction if rope is empty
        } else {
            std::cout << "Right baboon " << id << " is waiting. Rope is full." << std::endl;
        }
    } else {
        std::cout << "Right baboon " << id << " is waiting. Rope busy in other direction." << std::endl;
    }
    unlock();
}

int main() {
    int left_baboons, right_baboons;
    std::cout << "Enter number of left baboons: ";
    std::cin >> left_baboons;
    std::cout << "Enter number of right baboons: ";
    std::cin >> right_baboons;

    srand(time(0)); // Seed random number generator
    int total_baboons = left_baboons + right_baboons;

    for (int i = 0; i < total_baboons; ++i) {
        int random_direction = rand() % 2; // Randomly decide direction: 0 = left, 1 = right
        if (random_direction == 0 && left_baboons > 0) {
            left_baboon_cross(left_baboons--);
        } else if (right_baboons > 0) {
            right_baboon_cross(right_baboons--);
        }
    }

    return 0;
}


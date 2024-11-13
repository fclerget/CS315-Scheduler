/**
 * @file main.cpp
 * @brief Main function
 *
 * Main scheduler demo function.
 * Used to run all the scheduler examples.
 *
 * @author Fiya Clerget, Marcello Novak
 * @date 10/23/24
 */

/**
 * @file main.cpp
 * @brief Main function
 *
 * Main scheduler demo function.
 * Allows the user to select and run either the Stack, Queue, or Rate Monotonic Structured scheduler example.
 *
 * @date 10/31/24
 * @authors
 * Marcello Novak, Fiya Clerget
 */

#include "RoundRobin.h"
#include "Stack.h"
#include "Queue.h"
#include "RateMonotonic.h" // Include Rate Monotonic Scheduler
#include "RoundRobin.h"    // Include Round Robin Scheduler
#include <iostream> 

void displayMenu() {
    std::cout << "Select a scheduler to run:" << std::endl;
    std::cout << "S - Stack" << std::endl;
    std::cout << "Q - Queue" << std::endl;
    std::cout << "1 - Rate Monotonic Structured" << std::endl;  // New option
    std::cout << "2 - Round Robin Structured" << std::endl;
}

int main() {
    system("chcp 65001"); // Set UTF-8 code page for Windows cmd

    char choice;
    bool validInput = false;

    // Display the menu and get user input with validation
    while (!validInput) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 'S' || choice == 's') {
            Stack stackScheduler;
            stackScheduler.runExample();
            validInput = true;
        } else if (choice == 'Q' || choice == 'q') {
            Queue queueScheduler;
            queueScheduler.runExample();
            validInput = true;
        } else if (choice == '1') {  // Run Rate Monotonic Structured example
            RateMonotonicScheduler rmsScheduler;
            rmsScheduler.runExampleStructured();  // Run the structured example
            validInput = true;
        } else if (choice == '2') {  // Run Round Robin Structured example
            RoundRobinScheduler rrScheduler;
            rrScheduler.runExampleStructured();  // Run the structured example
            validInput = true;
        }else {
            std::cout << "Invalid input. Please enter 'S' for Stack, 'Q' for Queue, or '1' for Rate Monotonic Structured." << std::endl;
        }
    }

    return 0;
}

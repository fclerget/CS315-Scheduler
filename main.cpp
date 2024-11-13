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
    std::cout << "1 - Rate Monotonic" << std::endl;
    std::cout << "2 - Round Robin" << std::endl;
}

void displayRateMonotonicOptions() {
    std::cout << "Select a Rate Monotonic example to run:" << std::endl;
    std::cout << "1 - Structured" << std::endl;
    std::cout << "2 - Starved" << std::endl;
}

void displayRoundRobinOptions() {
    std::cout << "Select a Round Robin example to run:" << std::endl;
    std::cout << "1 - Structured" << std::endl;
    std::cout << "2 - Starved" << std::endl;
}

int main() {
    system("chcp 65001"); // Set UTF-8 code page for Windows cmd

    char choice;
    bool validInput = false;

    // Display the main menu and get user input with validation
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
        } else if (choice == '1') {  // Rate Monotonic Scheduler
            char rmChoice;
            bool rmValidInput = false;

            // Display the Rate Monotonic options menu
            while (!rmValidInput) {
                displayRateMonotonicOptions();
                std::cout << "Enter your choice: ";
                std::cin >> rmChoice;

                if (rmChoice == '1') {  // Run Structured example
                    RateMonotonicScheduler rmsScheduler(RateMonotonicScheduler::ExampleType::STRUCTURED);
                    rmsScheduler.runExample();
                    rmValidInput = true;
                } else if (rmChoice == '2') {  // Run Starved example
                    RateMonotonicScheduler rmsScheduler(RateMonotonicScheduler::ExampleType::STARVED);
                    rmsScheduler.runExample();
                    rmValidInput = true;
                } else {
                    std::cout << "Invalid input. Please enter '1' for Structured or '2' for Starved." << std::endl;
                }
            }
            validInput = true;
        } else if (choice == '2') {  // Round Robin Scheduler
            char rrChoice;
            bool rrValidInput = false;

            // Display the Round Robin options menu
            while (!rrValidInput) {
                displayRoundRobinOptions();
                std::cout << "Enter your choice: ";
                std::cin >> rrChoice;

                if (rrChoice == '1') {  // Run Structured example
                    RoundRobinScheduler rrScheduler(RoundRobinScheduler::ExampleType::STRUCTURED);
                    rrScheduler.runExample();
                    rrValidInput = true;
                } else if (rrChoice == '2') {  // Run Starved example
                    RoundRobinScheduler rrScheduler(RoundRobinScheduler::ExampleType::STARVED);
                    rrScheduler.runExample();
                    rrValidInput = true;
                } else {
                    std::cout << "Invalid input. Please enter '1' for Structured or '2' for Starved." << std::endl;
                }
            }
            validInput = true;
        } else {
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
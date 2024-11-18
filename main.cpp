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
#include "ASCII.h"         // Include ASCII color codes
#include <iostream> 

void displayMenu() {
    std::cout << "Select a scheduler to run:" << std::endl;
    std::cout << "S - Stack" << std::endl;
    std::cout << "Q - Queue" << std::endl;
    std::cout << "1 - Rate Monotonic" << std::endl;
    std::cout << "2 - Round Robin" << std::endl;
    std::cout << "K - Print Color Key" << std::endl;  // Added option
    std::cout << "E - Exit" << std::endl;
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

void displayColorKey() {
    std::cout << "\nColor Key:" << std::endl;

    setColor(COLOR_GREEN);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Running task" << std::endl;

    setColor(COLOR_RED);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Preempted task" << std::endl;

    setColor(COLOR_GRAY);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": No task" << std::endl;

    setColor(COLOR_BLUE);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Task created" << std::endl;

    setColor(COLOR_TURQUOISE);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Task created and executed" << std::endl;

    setColor(COLOR_YELLOW);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Task created but preempted" << std::endl;

    setColor(COLOR_ORANGE);
    std::cout << "█▓▒░";
    setColor(COLOR_WHITE);
    std::cout << ": Time unit run without task\n" << std::endl;
}

int main() {
    system("chcp 65001"); // Set UTF-8 code page for Windows cmd

    char choice;
    bool validInput = false;

    // Display the main menu and get user input with validation
    while (!validInput || choice != 'E' || choice != 'e') {
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
        } else if (choice == 'K' || choice == 'k') {
            displayColorKey();
            // Continue the loop without setting validInput to true
        } else if (choice == 'E' || choice == 'e'){
            std::cout << "Exiting Program." << std::endl;
            break;
        } else {
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
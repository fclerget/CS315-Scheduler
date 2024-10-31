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
 * Allows the user to select and run either the Stack or Queue scheduler example.
 *
 * @date 10/23/24
 */

#include "Stack.h"
#include "Queue.h"
#include <iostream>

void displayMenu() {
    std::cout << "Select a scheduler to run:" << std::endl;
    std::cout << "S - Stack" << std::endl;
    std::cout << "Q - Queue" << std::endl;
}

int main() {
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
        } else {
            std::cout << "Invalid input. Please enter 'S' for Stack or 'Q' for Queue." << std::endl;
        }
    }

    return 0;
}

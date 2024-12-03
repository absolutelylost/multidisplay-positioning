#define NOMINMAX // protects against discrepancy with max function in windows.h built in max()
#include <iostream>
#include <cstdlib> // for system() to clear the screen (optional)
#include <limits>
#include <string>
#include "headers/readConfig.hpp"
#include "headers/changePositions.hpp"
#include "headers/displayPositions.hpp"

using namespace std;
namespace DisplayPositioning
{
    bool configRead = false;

    void clearScreen()
    {
        system("cls");
    }

    void displayMenu()
    {
        cout << "====================\n";
        cout << "      Main Menu\n";
        cout << "1. Auto Arrange Displays\n";
        cout << "2. Current Display Positions\n";
        cout << "3. EXIT\n";
    }

    void handleSelection(int choice)
    {
        string substring;
        pair<std::vector<int>, std::vector<int>> configuration;
        switch (choice)
        {
        case 1:
            configuration = readConfig();
            changePositions(configuration.first, configuration.second, choice);
            cout << "Placing all displays into proper poistioning...\n";
            break;
        case 2:
            displayPositions(configuration.first, configuration.second, choice);
            cout << "Displaying Current Layout...\n";
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice...\n";
        }
    }

    int getValidInput(int min, int max)
    {
        int choice;
        while (true)
        {
            cout << "Please select an option (" << min << "-" << max << "): ";

            // check if the input is a valid integer value
            if (cin >> choice && choice >= min && choice <= max)
            {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
                return choice;                                                 // valid input, return the choice
            }
            else
            {
                // handle invalid input
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid characters
                cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            }
        }
    }

}

int main()
{
    int choice = 0;
    do
    {
        DisplayPositioning::clearScreen();
        DisplayPositioning::displayMenu();
        // Get valid user input
        choice = DisplayPositioning::getValidInput(1, 3); // The options range from 1 to 4

        DisplayPositioning::handleSelection(choice);

        if (choice != 3)
        {
            cout << "Press enter to continue...\n";
            cin.ignore(); // leftover newline
            cin.get();    // wait for the user to press enter
        }

    } while (choice != 3);

    return 0;
}

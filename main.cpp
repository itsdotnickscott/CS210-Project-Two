/******************************************************************************

 * main.cpp
 * Allows a user to input values for initial investment, monthly deposits,
 * and annual interest to calculate and analyze year-end values with the given
 * information.
 *
 * Name: Nick Scott
 * Assignment: Project Two
 * Course: CS-210
 * Last Modified: June 9, 2026

*******************************************************************************/

#include <iostream>
#include <format>
#include <memory>
#include "main.h"


int main()
{
    printHeader(); // print the name of the app

    std::unique_ptr<InterestCalculator> calculator{ std::make_unique<InterestCalculator>() }; // make a new calculator object
    inputInitialValues(*calculator); // ask the user to input starting values for calculator

    clearScreen(); // clear the screen
    printCalculatorValues(*calculator); // show the user the values they inputted

    int menuSelection{}; // stores the menu option the user wants to execute

    do { // loop until the user selects the option to exit the application
        printMenuOptions(); // print the available menu options to the user
        menuSelection = askForInt("\nMenu selection", MENU_VIEW_REPORTS, MENU_EXIT_APP); // allow the user to select a menu option
        // note: assumes first option is view reports and last option is exit
        processMenuSelection(menuSelection, *calculator); // execute the inputted menu selection
    } while (menuSelection != MENU_EXIT_APP);

    return 0;
}


/**
 * Prints the name of the company and app in a header border.
 */
void printHeader() {
    std::cout << std::format("{:=^{}}\n", "", InterestCalculator::TABLE_WIDTH); // top border
    std::cout << std::format("{:^{}}\n", "WELCOME TO AIRGEAD BANKING", InterestCalculator::TABLE_WIDTH); // bank name
    std::cout << std::format("{:^{}}\n", "Year-End Interest Calculator", InterestCalculator::TABLE_WIDTH); // app name
}


/**
 * Prints a caption with a border.
 * 
 * caption - The text to display.
 */
void printCaption(std::string caption) {
    std::cout << std::format("{:-^{}}\n", "", InterestCalculator::TABLE_WIDTH); // top border
    std::cout << std::format("{:^{}}\n", caption, InterestCalculator::TABLE_WIDTH); // caption
    std::cout << std::format("{:-^{}}\n", "", InterestCalculator::TABLE_WIDTH); // bottom border
}


/**
 * Asks the user to input values for the initial investment, monthly deposit, annual interest, and the number of years.
 *
 * calculator - The calculator object to set the values for
 */
void inputInitialValues(InterestCalculator& calculator) {
    printCaption("Please input the following info:"); // prompt user to enter info

    calculator.setInitialInvestment(askForDouble("Initial Investment", 0.01, "$", 2)); // input initial investment
    calculator.setMonthlyDeposit(askForDouble("Monthly Deposit", 0.01, "$", 2)); // input monthly deposit
    calculator.setAnnualInterest(askForDouble("Annual Interest", 0.0, "%")); // input annual interest
    calculator.setNumYears(askForInt("Number of Years", 1)); // input number of years
}


/**
 * Prints the initial investment, monthly deposit, annual interest, and the number of years of the calculator.
 *
 * calculator - The calculator object with the values to print
 */
void printCalculatorValues(InterestCalculator& calculator) {
    printCaption("Year-End Interest Calculator Values"); // app header

    // format the following calculator variables to two decimal places:
    std::string formattedInvestment = std::format("{:.2f}", calculator.getInitialInvestment()); 
    std::string formattedDeposit = std::format("{:.2f}", calculator.getMonthlyDeposit()); 
    std::string formattedInterest = std::format("{:.2f}", calculator.getAnnualInterest()); 
    
    // print calculator values:
    std::cout << "Initial Investment: $" << formattedInvestment << "\n";
    std::cout << "Monthly Deposit: $" << formattedDeposit << "\n";
    std::cout << "Annual Interest: " << formattedInterest << "%\n";
    std::cout << "Number of Years: " << calculator.getNumYears() << "\n";
}


/**
 * Prompts the user to input an integer between a given range (inclusive).
 * Includes error-checking for invalid data type (non-integers) and out of bounds.
 *
 * message - Prompt for the user printed to the console.
 * min - Lower bound for the number (inclusive)
 * max - Upper bound for the number (inclusive)
 *
 * Returns an integer that is within the given range.
 */
int askForInt(std::string prompt, int min, int max) {
    int userInt{}; // stores the user's input, intended to be a number
    bool inBounds{}; // stores whether user input is within given bounds

    do { // continue looping until user enters a number that is within the given range
        // print prompt to user with number bounds
        std::cout << prompt;
        std::cout << " (" << min << ((max == INT_MAX) ? "+" : " - " + std::to_string(max)) << "): ";

        // get user input then check for invalid data type
        if (!(std::cin >> userInt)) {
            std::cout << "\nPlease try again - Enter a whole number.\n"; // error message
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove input from buffer

            continue;
        }

        // check if user number is in bounds
        inBounds = ((userInt >= min) && (userInt <= max));
        if (!inBounds) {
            std::cout << "\nPlease try again - Enter a number between " << min << " and " << max << ".\n";
        }
    } while (!inBounds);

    return userInt;

}


/**
 * Prompts the user to input a double above a certain number (inclusive).
 * Includes error-checking for invalid data type (non-numbers) and out of bounds.
 *
 * prompt - Message for the user printed to the console.
 * min - Lower bound for the number (inclusive)
 * prefix - Symbol to show before number and input
 * maxDecimals - Max number of decimal places allowed for the number. Default is -1, which is no limit
 *
 * Returns a double that is above the given minimum.
 */
double askForDouble(std::string prompt, double min, std::string prefix, int maxDecimals) {
    double userDouble{}; // stores the user's input, intended to be a number
    bool aboveMin{}; // stores whether user input is above the given minimum
    bool invalidDecimals{}; // stores whether user's input has the correct number of decimal places

    do { // continue looping until user enters a number that is above the given minimum and has the correct number of decimals
        // print prompt to user with min
        std::cout << prompt;
        std::cout << " (at least " << prefix << min << "): " << prefix;

        // get user input then check for invalid data type
        if (!(std::cin >> userDouble)) {
            std::cout << "Please try again - Enter a number.\n"; // error message
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove input from buffer

            continue;
        }

        // check if user entered valid amount of decimal places
        invalidDecimals = maxDecimals != -1 && !hasMaxDecimalPlaces(userDouble, maxDecimals);
        if (invalidDecimals) {
            std::cout << "Please try again - Number can only have " << maxDecimals << " decimal places.\n\n"; // error message
            continue;
        }

        // check if user number is above the given minimum
        aboveMin = userDouble >= min;
        if (!aboveMin) {
            std::cout << "Please try again - Number must be at least " << prefix << min << ".\n\n"; // error message
        }
    } while (!aboveMin || invalidDecimals);

    return userDouble;
}


/**
 * Checks if a given double has a max amount of decimal places.
 * (ie. Check if 3.14 has a max of 2 decimal places - returns true)
 *
 * num - Number to check
 * numPlaces - Max amount of decimal places allowed
 *
 * Returns whether the number has the max amount of decimal places or less.
 */
bool hasMaxDecimalPlaces(double num, int numPlaces) {
    const double EPSILON = 1e-12; // margin of error to account for inaccuracy of floating-point numbers

    double multiplied{ num * std::pow(10.0, numPlaces)}; // scale the given number based on the number of decimal places to check
    double rounded{ std::round(multiplied) }; // round multiplied value to the nearest integer

    // if the multiplied number subtracted by the rounded number is 0, then the number has the correct amount of decimal places
    // considered a whole number if within EPSILON margin of error
    return std::abs(multiplied - rounded) < EPSILON;
}


/**
 * Prints all of the available options that can be taken within the app.
 */
void printMenuOptions() {
    printCaption("Please select a menu option:"); // print user instructions
    
    // print all menu options
    std::cout << "(1) Show Year-End Reports\n";
    std::cout << "(2) Show Calculator Values\n";
    std::cout << "(3) Edit Initial Investment\n";
    std::cout << "(4) Edit Monthly Deposit\n";
    std::cout << "(5) Edit Annual Interest Rate\n";
    std::cout << "(6) Edit Number of Years\n";
    std::cout << "(7) Reset All Values\n";
    std::cout << "(8) Exit Application\n";
}


/**
 * Executes a function of the app based off the user's selection.
 * 
 * option - The user inputted menu selection
 * calculator - The calculator object holding the values for reports
 */
void processMenuSelection(int option, InterestCalculator& calculator) {
    clearScreen(); // clear the screen

    switch (option) { // branch based off of user's selection
    case MENU_VIEW_REPORTS: // view the reports
        calculator.generateReports();
        break;

    case MENU_VIEW_VALUES: // view the calculator values
        printCalculatorValues(calculator);
        break;

    case MENU_EDIT_INVESTMENT: // ask user to input initial investment
        printCaption("Current Initial Investment: $" + std::format("{:.2f}", calculator.getInitialInvestment()));
        calculator.setInitialInvestment(askForDouble("New Initial Investment", 0.01, "$", 2));
        clearScreen(); // clear the screen
        printCalculatorValues(calculator); // show the user the values they inputted
        break;

    case MENU_EDIT_DEPOSIT: // ask user to input monthly deposit
        printCaption("Current Monthly Deposit: $" + std::format("{:.2f}", calculator.getMonthlyDeposit()));
        calculator.setMonthlyDeposit(askForDouble("New Monthly Deposit", 0.01, "$", 2));
        clearScreen(); // clear the screen
        printCalculatorValues(calculator); // show the user the values they inputted
        break;

    case MENU_EDIT_INTEREST: // ask user to input annual interest
        printCaption("Current Annual Interest: " + std::format("{:.2f}", calculator.getAnnualInterest()) + "%");
        calculator.setAnnualInterest(askForDouble("New Annual Interest", 0.0, "%"));
        clearScreen(); // clear the screen
        printCalculatorValues(calculator); // show the user the values they inputted
        break;

    case MENU_EDIT_YEARS:  // ask user to input number of years
        printCaption("Current Number of Years: " + std::to_string(calculator.getNumYears()));
        calculator.setNumYears(askForInt("New Number of Years", 1));
        clearScreen(); // clear the screen
        printCalculatorValues(calculator); // show the user the values they inputted
        break;

    case MENU_RESET_VALUES: // ask user to re-input all calculator values
        inputInitialValues(calculator);
        clearScreen(); // clear the screen
        printCalculatorValues(calculator); // show the user the values they inputted
        break;

    case MENU_EXIT_APP: // exit the app
        break; // do nothing

    default:
        "Something wrong has occurred."; // should not get to this point
        break;
    }
}


/**
 * Clears the screen.
 */
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";  // this sequence of characters clears the screen
}
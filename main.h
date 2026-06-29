#pragma once
#ifndef MAIN_H
#define MAIN_H


#include "interest_calculator.h"


const int MENU_VIEW_REPORTS{ 1 };
const int MENU_VIEW_VALUES{ 2 };
const int MENU_EDIT_INVESTMENT{ 3 };
const int MENU_EDIT_DEPOSIT{ 4 };
const int MENU_EDIT_INTEREST{ 5 };
const int MENU_EDIT_YEARS{ 6 };
const int MENU_RESET_VALUES{ 7 };
const int MENU_EXIT_APP{ 8 };


void printHeader();
void printCaption(std::string caption);
void inputInitialValues(InterestCalculator& calculator);
void printCalculatorValues(InterestCalculator& calculator);
int askForInt(std::string prompt, int min, int max = INT_MAX);
double askForDouble(std::string prompt, double min, std::string prefix = "", int maxDecimals = -1);
bool hasMaxDecimalPlaces(double num, int numPlaces);
void printMenuOptions();
void processMenuSelection(int option, InterestCalculator& calculator);
void clearScreen();


#endif
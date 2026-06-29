/******************************************************************************

 * interest_calculator.cpp
 * Calculator objects stores information for initial investment, monthly deposits,
 * and annual interest. Generates year-end reports with the given information.
 *
 * Name: Nick Scott
 * Assignment: Project Two
 * Course: CS-210
 * Last Modified: June 9, 2026

*******************************************************************************/

#include <iostream>
#include <format>
#include "interest_calculator.h"


/**
 * Calculates the end-year balances for each year using the given user values.
 *
 * withMonthlyDeposits - Calculate end-year balances with adding monthly deposit. Default false.
 *
 * Returns a vector holding the end-year balances of each year starting with year 0 (the initial investment).
 */
std::vector<double> InterestCalculator::m_calculateYearEndBalances(bool withMonthlyDeposits) const {
    int totalMonths{ getNumYears() * m_MONTHS_IN_YEAR }; // calculate the total months within the time frame given
    double deposit{ withMonthlyDeposits ? getMonthlyDeposit() : 0.0}; // holds monthly deposit, set deposit to 0 if calculating without monthly deposits
    double monthlyInterest{ (getAnnualInterest() / 100) / m_MONTHS_IN_YEAR }; // calculate the monthly interest by turning into percent and dividing by months in year

    std::vector<double> yearEndValues{}; // vector to hold the end balance for each year

    double currAmount{ getInitialInvestment() }; // will store the balance of each year, idx represents how many years since initial investment
    yearEndValues.push_back(currAmount); // add the initial investment to the vector (year 0 represents initial investment)

    for (int month = 1; month <= totalMonths; month++) { // loop for every month in given time frame
        currAmount += deposit; // add monthly deposit, if applicable
        currAmount += currAmount * monthlyInterest; // add monthly interest

        if (month % 12 == 0) { // if currently calculating the end balance of the last month of the year
            yearEndValues.push_back(currAmount); // add to end-year balances vector
        }
    }

    return yearEndValues; // return end year balances
}


/**
 * Formats and prints a given report with end-year balances for the user.
 *
 * report - Vector object holding the end-balances of each year (see m_calculateYearEndBalances())
 * reportName - Text to display at the top of the chart
 * monthlyDeposit - The amount deposited each month. Default is 0.0
 */
void InterestCalculator::m_printReport(std::vector<double> report, std::string reportName, double monthlyDeposit) const {
    std::cout << std::format("{:=^{}}\n", "", TABLE_WIDTH); // top border
    std::cout << std::format("{:^{}}\n", reportName, TABLE_WIDTH); // report name
    std::cout << std::format("{:=^{}}\n", "", TABLE_WIDTH); // title border
    std::cout << std::format("{:>{}}{:>{}}{:>{}}\n", // column names
        "Year", m_YEAR_WIDTH,
        "End Balance", m_BALANCE_WIDTH,
        "Earned Interest", m_INTEREST_WIDTH);
    std::cout << std::format("{:-^{}}\n", "", TABLE_WIDTH); // bottom border

    double lastBalance = report[0]; // stores the balance of the previously processed year (starts with initial investment)
    double yearlyDeposit = monthlyDeposit * m_MONTHS_IN_YEAR; // calculates how much money is deposited within a given year

    for (int year = 1; year < report.size(); year++) { // loops for each year in the report
        std::string formattedBalance = "$" + std::format("{:.2f}", report[year]); // formats the end-year balance to two decimal places
        std::string formattedInterest = "$" + std::format("{:.2f}", report[year] - lastBalance - yearlyDeposit); // formats the end-year earned interest to two decimal places

        std::cout << std::format("{:>{}}{:>{}}{:>{}}\n", // print each column onto the table
            year, m_YEAR_WIDTH,
            formattedBalance, m_BALANCE_WIDTH,
            formattedInterest, m_INTEREST_WIDTH);

        lastBalance = report[year]; // update the end-balance for the year for next iteration
    }
}


/**
 * Generates two reports with the given investment/interest values.
 * One report does not include monthly deposits and the other report does.
 * Prints both reports to the console.
 */
void InterestCalculator::generateReports() const {
    std::vector<double> reportNoDeposits = m_calculateYearEndBalances(); // generate the year-end report without deposits
    std::vector<double> reportWithDeposits = m_calculateYearEndBalances(true); // print the year-end report with deposits

    m_printReport(reportNoDeposits, m_NO_DEPOSITS_REPORT_NAME); // generate the year-end report with deposits
    m_printReport(reportWithDeposits, m_WITH_DEPOSITS_REPORT_NAME, getMonthlyDeposit()); // print the year-end report with deposits
}
#pragma once
#ifndef INTEREST_CALCULATOR_H
#define INTEREST_CALCULATOR_H


#include <string>
#include <vector>


// InterestCalculator stores user-inputted values and calculates the end-year balance of an account with monthly interest.
class InterestCalculator {
private:
    const int m_MONTHS_IN_YEAR{ 12 }; // represents the total number of months in a year
    const int m_YEAR_WIDTH{ TABLE_WIDTH / 5 }; // represents the column width for the year - 20% the width of the table
    const int m_BALANCE_WIDTH{ TABLE_WIDTH * 2 / 5 }; // represents the column width for the end-year balance - 40% the width of the table
    const int m_INTEREST_WIDTH{ TABLE_WIDTH * 2 / 5 };  // represents the column width for interest accrued - 40% the width of the table

    // table names
    const std::string m_NO_DEPOSITS_REPORT_NAME{ "Year-End Balance and Interest Report (No Monthly Deposits)" };
    const std::string m_WITH_DEPOSITS_REPORT_NAME{ "Year-End Balance and Interest Report (With Monthly Deposits)" };

    double m_initialInvestment{}; // stores the user's initial dollar amount invested into the account
    double m_monthlyDeposit{}; // stores the user's dollar amount deposited to the account each month
    double m_annualInterest{}; // stores the user's annual interest rate applied to the account
    int m_numYears{}; // stores the time frame the user wishes to view

    // private member functions
    std::vector<double> m_calculateYearEndBalances(bool withMonthlyDeposits = false) const;
    void m_printReport(std::vector<double> report, std::string reportName, double monthlyDeposit = 0.0) const;

public:
    static const int TABLE_WIDTH{ 70 }; // represents the width of the report table in characters

    // default constructor
    InterestCalculator() = default;

    // parameterized constructor
    InterestCalculator(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterest, int t_numYears) :
        m_initialInvestment(t_initialInvestment),
        m_monthlyDeposit(t_monthlyDeposit),
        m_annualInterest(t_annualInterest),
        m_numYears(t_numYears) {}

    // copy constructor - used https://www.geeksforgeeks.org/cpp/copy-constructor-in-cpp/
    InterestCalculator(const InterestCalculator& calculator) :
        m_initialInvestment(calculator.getInitialInvestment()),
        m_monthlyDeposit(calculator.getMonthlyDeposit()),
        m_annualInterest(calculator.getAnnualInterest()),
        m_numYears(calculator.getNumYears()) {}

    // accessor functions
    double getInitialInvestment() const { return m_initialInvestment; }
    double getMonthlyDeposit() const { return m_monthlyDeposit; }
    double getAnnualInterest() const { return m_annualInterest; }
    int getNumYears() const { return m_numYears; }

    // mutator functions
    void setInitialInvestment(double t_initialInvestment) { m_initialInvestment = t_initialInvestment; }
    void setMonthlyDeposit(double t_monthlyDeposit) { m_monthlyDeposit = t_monthlyDeposit; }
    void setAnnualInterest(double t_annualInterest) { m_annualInterest = t_annualInterest; }
    void setNumYears(int t_numYears) { m_numYears = t_numYears; }

    // public member functions
    void generateReports() const;
};


#endif
/**
 * @file menu.h
 *
 * @brief This file contains the header declaring the class for menu.
 *
 * @details Contains declarations of the menu.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono> 
#include <vector>

using namespace std;

/**
 * @class Menu
 *
 * @brief Represents a menu for handling operations.
 *
 * @details Provides functionalities to display options, retrieve values between dates,
 * retrieve timestamps, and convert timestamps to time points.
 */
class Menu {
public:
    Menu();
    ~Menu();
    /**
     * @brief Displays main options.
     */
    void mainOptions();
    /**
     * @brief Retrieves values between specified dates from a file.
     *
     * @param[in] initialDate is the starting date.
     * @param[in] finalDate is the ending date.
     * @param[in] fileName is the name of the file to read from.
     */
    void getValuesBetweenDates(string initialDate, string finalDate, string fileName);
    /**
     * @brief Retrieves the timestamp from a file and displays it.
     *
     * @param[in] fileName is the name of the file to read from.
     */
    void getTimestamp(string fileName);
    /**
     * @brief Converts a timestamp string to a time point.
     *
     * @param[in] timestamp is the timestamp string to convert.
     * @return The converted time point.
     */
    chrono::system_clock::time_point convertToTime(string timestamp);
};

#endif /* MENU_H_ */

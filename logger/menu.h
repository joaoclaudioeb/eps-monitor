/**
 * @file menu.h
 *
 * @brief Header file for defining the class for menu.
 *
 * @details It implements functionalities related to the menu.
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

class Menu {
public:
    Menu();
    ~Menu();

    void mainOptions();
    void getValuesBetweenDates(std::string initialDate, std::string finalDate, std::string fileName);
    void getTimestamp(std::string fileName);
    chrono::system_clock::time_point convertToTime(string timestamp);
};

#endif /* MENU_H_ */

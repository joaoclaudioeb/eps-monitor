/**
 * @file menu.cpp
 *
 * @brief This file contains the source code defining the class for menu.
 *
 * @details It implements functionalities related to the menu.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "menu.h"


Menu::Menu(){}
Menu::~Menu(){}

void Menu::mainOptions(){
    int choice;

    while (1) {
        // Display menu options
        cout << "Main Menu Options:" << "\n";
        cout << "1. Get values between dates" << "\n";
        cout << "2. Get timestamp" << "\n";
        cout << "3. Exit" << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Get values between dates
                string initialDate, finalDate, fileName;
                cout << "Enter initial date (DD/MM/YY): ";
                cin >> initialDate;
                cout << "Enter final date (DD/MM/YY): ";
                cin >> finalDate;
                fileName = "serial_log.txt";
                getValuesBetweenDates(initialDate, finalDate, fileName);
                break;
            }
            case 2: {
                // Get timestamp
                string fileName;
                fileName = "serial_log.txt";
                getTimestamp(fileName);
                break;
            }
            case 3: {
                // Exit
                cout << "Exiting menu..." << "\n";
                return;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << "\n";
                break;
            }
        }
    }
}

void Menu::getValuesBetweenDates(string initialDate, string finalDate, string fileName){
    int print = 0;
    
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        cout << "\n";
        while (getline(file, line)) {
      
            if (line.find(initialDate) != string::npos) {
                print = 1;
            }

            if (print) {
                cout << line << "\n";
            }

            if (line.find(finalDate) != string::npos) {
                cout << "\n";
                print = 0;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file! \n";
    }
}

void Menu::getTimestamp(string fileName){

    ifstream file(fileName);

    if (file.is_open()) {
        string line;
        vector<string> lines;

        // Read lines and store them in a vector
        while (getline(file, line)) {
            lines.push_back(line);
        }

        if (!lines.empty()) {
            string firstTimestamp = lines.front().substr(5, 16); // Extract timestamp
            string lastTimestamp = lines.back().substr(5, 16);   // Extract timestamp

            cout << "First Timestamp: " << firstTimestamp << "\n";
            cout << "Last Timestamp: " << lastTimestamp << "\n";

            // Convert timestamps to time_point
            chrono::system_clock::time_point firstTime = convertToTime(firstTimestamp);
            chrono::system_clock::time_point lastTime = convertToTime(lastTimestamp);

            // Calculate elapsed time
            chrono::duration<double> elapsedTime = lastTime - firstTime;

            cout << "Elapsed time between first and last log: " << elapsedTime.count() << " seconds" << "\n";
        } else {
            cerr << "File is empty!" << "\n";
        }

        lines.clear(); // Clear the vector for the next read
        file.close();
    } else {
        cerr << "Unable to open file!" << "\n";
    }

}

// Function to convert timestamp to time_point
chrono::system_clock::time_point Menu::convertToTime(string timestamp){
    /**
     * Initialize a 'tm' struct, as described:
     * struct tm {
     *     int tm_sec;  
     *     int tm_min;  
     *     int tm_hour;  
     *     int tm_mday;  
     *     int tm_mon;   
     *     int tm_year;  
     *     int tm_wday;  
     *     int tm_yday;  
     *     int tm_isdst; 
     * };
     *
     */
    tm t = tm{};
    /**
     * Parsing a string into a 'tm', a structured 
     * representation of date and time.
     */   
    strptime(timestamp.c_str(), "%d/%m/%Y %H:%M:%S", &t);
    /**
     * Conversion of 'tm' struct to a 'time_point' object.
     * mktime() first converts it to 'time_t' object, and
     * then converts to 'time_point' object.
     */
    return chrono::system_clock::from_time_t(mktime(&t));
}

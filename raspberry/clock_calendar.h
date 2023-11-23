/**
 * @file clock_calendar.h
 *
 * @brief Header file defining the classes to get events' date and time.
 *
 * @details Contains declarations of classes and functionalities related to the management of date and time.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef CLOCK_CALENDAR_H_
#define CLOCK_CALENDAR_H_

#include <string>
#include <iostream>

/**
 * @class Clock
 *
 * @brief Represents time (hours, minutes, seconds).
 *
 * @details Provides functionalities to manage the time.
 */
class Clock {
 protected:
	int hr, min, sec, is_pm;
 public:
	Clock(int h, int s, int m, int pm);
	~Clock();
    /**
     * @brief Advances the time by the given seconds.
     *
     * @param[in] elapsedSeconds is the number of seconds to advance the time.
     *
     * @details Updates the time based on the provided elapsed time (given in seconds).
     */
	void advance(int elapsedSeconds);
};

/**
 * @class Calendar
 *
 * @brief Represents a date (month, day, year).
 *
 * @details Provides functionalities to manage the date.
 */
class Calendar {
 protected:
	int mo, day, yr;
 public:
	Calendar(int m, int d, int y);
	~Calendar();

    /**
     * @brief Advances the date.
     *
     * @details Updates the date considering internal logic.
     */
	void advance();
};

/**
 * @class ClockCalendar
 *
 * @brief Represents both time and date by inheriting Clock and Calendar classes.
 *
 * @details Provides functionalities to manage both time and date simultaneously.
 */
class ClockCalendar : public Clock, public Calendar {
 private:
    uint64_t lastAdvanceTime;
 public:
    ClockCalendar();
    ~ClockCalendar();
    
    /**
     * @brief Advances both time and date.
     *
     * @details Updates both time and date based on internal calculations.
     */
    void advance();

    /**
     * @brief Converts an integer to a string.
     *
     * @param[in] num is the integer to convert.
     * @return The string representation of the integer.
     *
     * @details Converts an integer to its string representation.
     */
    string intToString(int num) const {
        string result = "";
        if (num == 0) {
            result = "0";
        } else {
            while (num > 0) {
                char digit = '0' + (num % 10);
                result = digit + result;
                num /= 10;
            }
        }
        return result;
    }

    /**
     * @brief Overrides the '+' operator to generate a string with a representation of date and time.
     *
     * @return The concatenated string of date and time.
     *
     * @details Combines date and time into a single string representation.
     */
    string operator+() const {
        return intToString(day) + "/"
            + intToString(mo) + "/"
            + intToString(yr) + " "
            + intToString(hr) + ":"
            + intToString(min) + ":"
            + intToString(sec);
    }
};

#endif /* CLOCK_CALENDAR_H_ */

/**
 * @file clock_calendar.cpp
 *
 * @brief This file contains the implementation of classes to get events' date and time.
 *
 * @details It Implements the management of date and time, considering hours, minutes, seconds, as well as
 * months, days and years.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "clock_calendar.h"

Clock::Clock(int h, int s, int m, int pm){
	hr = h;
	min = m;
	sec = s;
	is_pm = pm;
}
Clock::~Clock(){}

void Clock::advance(int elapsedSeconds){
    if (elapsedSeconds > 0) {
        sec += elapsedSeconds;
        int extraMinutes = sec / 60;
        sec %= 60;
        min += extraMinutes;
        int extraHours = min / 60;
        min %= 60;
        hr += extraHours;
        hr %= 24;
        is_pm = (hr >= 12);
    }
}

Calendar::Calendar(int m, int d, int y){
	mo = m;
	day = d;
	yr = y;
}
Calendar::~Calendar(){}

void Calendar::advance(){
	if(++day > 30){
		day = 1;
		if(++mo > 12){
			mo = 1;
			yr++;
		}
	}
}


ClockCalendar::ClockCalendar() : Clock(0, 0, 0, 0), Calendar(11, 16, 2023), lastAdvanceTime(0) {}
ClockCalendar::~ClockCalendar(){}

void ClockCalendar::advance(){
    int was_pm = is_pm;
    
    int64_t currentTime = time_us_64(); // Obtain the elapsed time since the initialization, in us 
    int64_t elapsedTime = currentTime - lastAdvanceTime;
    int elapsedSeconds = elapsedTime / 1000000; // Convert the time in us to s
    
	 
	Clock::advance(elapsedSeconds);
	if (was_pm && !is_pm)
        Calendar::advance();
    lastAdvanceTime = currentTime;
}

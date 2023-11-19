#include <string>
#include <iostream>

using namespace std;

class Clock {
 protected:
	int hr, min, sec, is_pm;
 public:
	Clock(int h, int s, int m, int pm);
	~Clock();
	void advance(int elapsedSeconds);
};

class Calendar {
 protected:
	int mo, day, yr;
 public:
	Calendar(int m, int d, int y);
	~Calendar();
	void advance();
};

class ClockCalendar : public Clock, public Calendar {
 private:
    uint64_t lastAdvanceTime;
 public:
    ClockCalendar();
    ~ClockCalendar();
    void advance();
    
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

    string operator+() const {
        return intToString(day) + "/" + intToString(mo) + "/" + intToString(yr) + " " + intToString(hr) + ":" + intToString(min) + ":" + intToString(sec);
    }
};

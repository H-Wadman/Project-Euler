#include <iostream>

//All dates in the document follows the ISO-8601 standard of YYYY-MM-DD.

/**Checks if a year was a leap year
 * @param year: an integer
 * @return true if year is a leap year, false otherwise
*/
bool isLeapYear(int year)
{
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return (year % 4 == 0);
}

/**Returns the numer of days in a month on a specific year
 * @param year - the year of the month we want to check (1 == Jan, 2 == Feb and so on)
 * @param month - the month we want to check
 * @return the number of days in "month" on the year "year"
*/
int daysInMonth(int year, int month)
{
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    if (month == 2) return ((isLeapYear(year) ? 29 : 28));

    return 31;

}

/**Returns the number of days between two dates; second date assumed later than first
 * @param y1 the year of the first date
 * @param m1 the month of the first date
 * @param d1 the day of the first date
 * @param y2 the year of the second date.
 * @param m2 the month of the second date
 * @param d2 the day of the second date
*/
int dateDifference(int y1, int m1, int d1, int y2, int m2, int d2)
{
    int difference {0};
    difference += d2 - d1;

    for (int i {0}; i < m2 - m1; i++)
    {
        difference += daysInMonth(y2, m1 + i);
    }

    for (int i {0}; i < y2 - y1; i++)
    {
        isLeapYear(y1+i) ? difference += 366 : difference += 365;
    }

    return difference;
}

void functionTest(int test, int test2)
{
    std::cout << "Using " << test << " as test year\n";
    std::cout << "isLeapYear: " << isLeapYear(test) << '\n';
    std::cout << "The number of days in February " << test << " was: " << daysInMonth(test, 2) << '\n';
    std::cout << "The number of days between February 1st and March 1st " << test << ": " << dateDifference(test, 2, 1, test, 3, 1) << '\n';
    std::cout << "The number of days between February 1st of " << test << " and March 1st of " << test2 << ": " << dateDifference(test, 2, 1, test2, 3, 1) << '\n';
}
/**Checks if a certain date after  was a sunday
 * @param y the year of the checked date 
 * @param m the month of the checked date
 * @param d the day of the checked date
*/
bool isSunday(int y, int m, int d)
{
    return dateDifference(1900, 1, 1, y, m, d) % 7 == 6;

}

int main()
{
    int counter {0};
    
    for (int y {1901}; y <= 2000; y++)
    {
        for (int m {1}; m <= 12; m++)
        {
            if (isSunday(y, m, 1)) ++counter;
        }
    }
    std::cout << counter << '\n';
    
    return 0;
}
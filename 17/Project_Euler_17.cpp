#include <iostream>

/** Return the letter count of digits
 *  @param n a number 1-9
 *  @return the letter count of digit n
**/
int countLetterOfDigits(int n)
{
    if (n == 0) return 0; // "Zero" doesn't get pronounced in numbers ("forty" not "four-zero or forty-zero")
    if (n == 1) return 3; // "One" has 3 letters and so forth
    if (n == 2) return 3; 
    if (n == 3) return 5;
    if (n == 4) return 4;
    if (n == 5) return 4;
    if (n == 6) return 3;
    if (n == 7) return 5;
    if (n == 8) return 5;
    if (n == 9) return 4;

    std::cout << "Warning1\n";
    return -1;
}

/** Returns the letter count of tens (20, 30, 40 etc)
 *  @param n a number 2-9
 *  @return the letter count of n*10
**/
int countLettersOfTens(int n)
{
    if (n == 2) return 6; //"Twenty" has 6 letters and so forth
    if (n == 3) return 6;
    if (n == 4) return 5;
    if (n == 5) return 5;
    if (n == 6) return 5;
    if (n == 7) return 7;
    if (n == 8) return 6;
    if (n == 9) return 6;

    std::cout << "Warning2\n";
    return -1;
}

/** Returns the letters of a two digit number
 *  @param n a positive integer 1-99 inclusive
 *  @return the letter count of n
**/
int countLettersOfTwoDigitNumber(int n)
{
    if (n < 10)
    {
        return countLetterOfDigits(n);
    }
    else if (n > 19)
    {
        return countLettersOfTens(n/10) + countLetterOfDigits(n % 10);
    }
    else
    {
        if (n == 10) return 3;  //Ten
        if (n == 11) return 6;  //Eleven
        if (n == 12) return 6;  //Twelve
        if (n == 13) return 8;  //Thirteen
        if (n == 14) return 8;  //Fourteen
        if (n == 15) return 7;  //Fifteen
        if (n == 16) return 7;  //Sixteen
        if (n == 17) return 9;  //Seventeen
        if (n == 18) return 8;  //Eighteen
        if (n == 19) return 8;  //Nineteen
    }
    
    std::cout << "Warning3\n";
    return -1;
}


/** Returns the letter count of a number
 *  @param n a positive integer 1-1000 inclusive
 *  @return the letter count of n
**/
int countLetters(int n)
{
    if (n == 1000)
    {
        return 11; //One thousand
    }
    if (n > 99)
    {
        // + 10 because of "hundred" (7) and "and" (3)
        if (n % 100 == 0) return countLetterOfDigits(n/100) + 7;
        return countLetterOfDigits(n/100) + 10 + countLettersOfTwoDigitNumber(n % 100); 
    }
    // if n is <99
    return countLettersOfTwoDigitNumber(n);

    std::cout << "Warning4\n";
    return -1;
}




int main()
{
    int countOfRound {};
    u_int32_t uLetterSum {0};
    for (int i {1}; i <= 1000; i++)
    {
        uLetterSum += countLetters(i);
    }


    std::cout << uLetterSum << '\n';

    return 0;
}
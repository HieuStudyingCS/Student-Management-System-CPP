#pragma once
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

class DateUtils
{
public:
    static void normalizeDate(string &dateStr)
    {
        if (dateStr.length() < 3)
            return;
        if (dateStr[1] == '/')
            dateStr = '0' + dateStr;
        if (dateStr.length() > 4 && dateStr[4] == '/')
            dateStr.insert(3, "0");
    }

    static int getCurrentAcademicYear()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        int year = now->tm_year + 1900;
        int month = now->tm_mon + 1;
        return (month < 9) ? year - 1 : year;
    }
};

class ValidationUtils
{
public:
    static bool isValidMSSV(int mssv)
    {
        return (10000000 <= mssv && mssv <= 99999999);
    }
    static void clearInputBuffer()
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }
};
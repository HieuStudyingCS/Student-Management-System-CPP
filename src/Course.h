#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Course
{
private:
    string maMon;
    int tinChi;
    double gpa;

public:
    Course(string id, int credits, double score) : maMon(id), tinChi(credits), gpa(score) {}

    int getTinChi() const { return tinChi; }
    double getGPA() const { return gpa; }

    friend ostream &operator<<(ostream &os, const Course &course)
    {
        os << left << setw(15) << course.maMon << setw(15) << course.tinChi << course.gpa << "\n";
        return os;
    }
};
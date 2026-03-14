#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Course.h"

using namespace std;

class Semester
{
private:
    string name;
    vector<Course> courses;

public:
    Semester(string semesterName) : name(semesterName) {}

    void addCourse(const Course &course) { courses.push_back(course); }
    bool isEmpty() const { return courses.empty(); }
    string getName() const { return name; }

    int getTotalCredits() const
    {
        int total = 0;
        for (const auto &course : courses)
        {
            total += course.getTinChi();
        }
        return total;
    }

    double getAverageGPA() const
    {
        if (courses.empty())
            return 0.0;
        double totalPoints = 0;
        int totalCredits = 0;
        for (const auto &course : courses)
        {
            totalPoints += course.getGPA() * course.getTinChi();
            totalCredits += course.getTinChi();
        }
        return (totalCredits == 0) ? 0.0 : (totalPoints / totalCredits);
    }

    friend ostream &operator<<(ostream &os, const Semester &sem)
    {
        if (sem.isEmpty())
        {
            os << "Không có môn học nào được đăng ký trong học kỳ này.\n";
            return os;
        }
        os << left << setw(15) << "Mã môn" << setw(15) << "Tín chỉ" << "GPA\n";
        os << "------------------------------------------\n";
        for (const auto &course : sem.courses)
            os << course;
        os << "------------------------------------------\n";
        os << "Tổng số tín chỉ: " << sem.getTotalCredits() << "\n";
        os << "Điểm trung bình học kỳ: " << fixed << setprecision(2) << sem.getAverageGPA() << "\n";
        return os;
    }
};
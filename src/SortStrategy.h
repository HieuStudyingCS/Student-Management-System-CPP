#pragma once
#include <vector>
#include <algorithm>
#include "Student.h"

using namespace std;

class ISortStrategy
{
public:
    virtual void sortStudents(vector<Student> &students) = 0;
    virtual ~ISortStrategy() = default;
};

class SortByMSSV : public ISortStrategy
{
public:
    void sortStudents(vector<Student> &students) override
    {
        sort(students.begin(), students.end());
    }
};
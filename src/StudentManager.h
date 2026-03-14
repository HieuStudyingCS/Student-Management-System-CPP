#pragma once
#include <vector>
#include "Student.h"
#include "SortStrategy.h"

using namespace std;

class StudentManager
{
private:
    vector<Student> studentList;
    ISortStrategy *sortStrategy;

public:
    StudentManager(ISortStrategy *strategy) : sortStrategy(strategy) {}

    void addStudent(const Student &student) { studentList.push_back(student); }

    void sortData()
    {
        if (sortStrategy)
            sortStrategy->sortStudents(studentList);
    }

    const Student *findStudentByMSSV(int mssv) const
    {
        for (const auto &student : studentList)
            if (student == mssv)
                return &student;
        return nullptr;
    }

    bool isEmpty() const { return studentList.empty(); }
};
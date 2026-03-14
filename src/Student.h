#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Semester.h"

using namespace std;

class Student
{
private:
    int mssv;
    int khoaSV;
    string hoTen;
    string ngaySinh;
    vector<Semester> semesters;

public:
    Student() : mssv(0), khoaSV(0) {}
    Student(int id, int khoa, string name, string dob)
        : mssv(id), khoaSV(khoa), hoTen(name), ngaySinh(dob) {}

    int getMSSV() const { return mssv; }
    int getNamNhapHoc() const { return 2005 + khoaSV; }

    void addCourseFromCSV(int kySo, string tenHK, const Course &course)
    {
        while (semesters.size() < kySo)
        {
            semesters.push_back(Semester(tenHK));
        }
        semesters[kySo - 1].addCourse(course);
    }

    void printSemesterInfo(int semesterIndex) const
    {
        if (semesterIndex < 1 || semesterIndex > semesters.size())
        {
            cout << "\n[!] Sinh viên chưa có dữ liệu ở học kỳ " << semesterIndex << ".\n";
            return;
        }
        const Semester &sem = semesters[semesterIndex - 1];
        cout << "\n--- CHI TIẾT HỌC KỲ " << semesterIndex << " (" << sem.getName() << ") ---\n";
        cout << sem;
        cout << "=================================================\n";
    }

    bool operator<(const Student &other) const { return this->mssv < other.mssv; }
    bool operator==(int targetMSSV) const { return this->mssv == targetMSSV; }

    friend ostream &operator<<(ostream &os, const Student &sv)
    {
        os << "Họ và tên: " << sv.hoTen << "\n"
           << "MSSV: " << sv.mssv << "\n"
           << "Ngày sinh: " << sv.ngaySinh << "\n"
           << "Khóa: " << sv.khoaSV << " (Năm nhập học: " << sv.getNamNhapHoc() << ")\n";
        return os;
    }
};
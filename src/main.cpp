#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>

#include "Utils.h"
#include "Course.h"
#include "Semester.h"
#include "Student.h"
#include "SortStrategy.h"
#include "StudentManager.h"

using namespace std;

void loadDataFromCSV(StudentManager &manager, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "[LỖI TỚI MẠNG] Không tìm thấy file '" << filename << "' trong thư mục gốc!\n";
        return;
    }

    string line;
    getline(file, line);
    map<int, Student> studentMap;
    int count = 0;
    int lineNum = 1;

    while (getline(file, line))
    {
        lineNum++;
        if (line.empty())
            continue;

        stringstream ss(line);
        string mssv_str, khoa_str, hoTen, ngaySinh, kySo_str, tenHK, maMon, tinChi_str, gpa_str;

        getline(ss, mssv_str, ',');
        getline(ss, khoa_str, ',');
        getline(ss, hoTen, ',');
        getline(ss, ngaySinh, ',');
        getline(ss, kySo_str, ',');
        getline(ss, tenHK, ',');
        getline(ss, maMon, ',');
        getline(ss, tinChi_str, ',');
        getline(ss, gpa_str, ',');

        try
        {
            int mssv = stoi(mssv_str);
            int khoa = stoi(khoa_str);
            int kySo = stoi(kySo_str);
            int tinChi = stoi(tinChi_str);
            double gpa = stod(gpa_str);

            if (studentMap.find(mssv) == studentMap.end())
            {
                studentMap[mssv] = Student(mssv, khoa, hoTen, ngaySinh);
                count++;
            }
            studentMap[mssv].addCourseFromCSV(kySo, tenHK, Course(maMon, tinChi, gpa));
        }
        catch (const invalid_argument &e)
        {
            cout << "[CẢNH BÁO] Sai kiểu dữ liệu tại dòng " << lineNum << ". Đã bỏ qua.\n";
        }
        catch (const out_of_range &e)
        {
            cout << "[CẢNH BÁO] Số quá lớn tại dòng " << lineNum << ". Đã bỏ qua.\n";
        }
    }

    for (auto const &[key, val] : studentMap)
    {
        manager.addStudent(val);
    }
    cout << "=> Nạp thành công " << count << " sinh viên hợp lệ từ file " << filename << "!\n";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    cout << "HỆ THỐNG QUẢN LÝ SINH VIÊN UIT (OOP + SAFE FILE IO)\n";
    cout << "========================================\n";

    SortByMSSV sortStrategy;
    StudentManager systemManager(&sortStrategy);

    cout << "Đang nạp dữ liệu từ file data.csv...\n";

    loadDataFromCSV(systemManager, "data.csv");

    if (systemManager.isEmpty())
    {
        cout << "Hệ thống trống. Kết thúc chương trình.\n";
        return 0;
    }

    systemManager.sortData();

    while (true)
    {
        cout << "\n\nVui lòng nhập MSSV muốn tra cứu (Nhập 0 để thoát): ";
        int mssv_can_tim;
        if (!(cin >> mssv_can_tim))
        {
            cout << "Vui lòng chỉ nhập số!\n";
            ValidationUtils::clearInputBuffer();
            continue;
        }

        if (mssv_can_tim == 0)
        {
            cout << "Đang thoát hệ thống...\n";
            break;
        }

        const Student *student = systemManager.findStudentByMSSV(mssv_can_tim);
        if (student == nullptr)
        {
            cout << "Không tìm thấy Sinh Viên có MSSV " << mssv_can_tim << "!\n";
            continue;
        }

        int hocKyTraCuu;
        cout << "Vui lòng nhập số thứ tự kỳ học muốn tra cứu (1 -> 8): ";
        if (!(cin >> hocKyTraCuu) || hocKyTraCuu < 1 || hocKyTraCuu > 8)
        {
            cout << "Học kỳ không hợp lệ!\n";
            ValidationUtils::clearInputBuffer();
            continue;
        }

        cout << "\n================ KẾT QUẢ TRA CỨU ================\n";
        cout << *student;
        student->printSemesterInfo(hocKyTraCuu);
    }
    return 0;
}
import csv
import random

first_names = ["Nguyen", "Tran", "Le", "Pham", "Hoang", "Huynh", "Phan", "Vu", "Vo", "Dang", "Bui", "Do"]
middle_names = ["Van", "Thi", "Huu", "Ngoc", "Quang", "Minh", "Thu", "Gia", "Xuan", "Hoai"]
last_names = ["An", "Binh", "Chau", "Duy", "Hieu", "Khoa", "Linh", "Mai", "Nam", "Phong", "Quan", "Trang", "Vy", "Yen"]

# Bổ sung thêm nhiều môn học để bốc thăm đủ 6-8 môn
subjects = [
    ("IT001", 4), ("CS106", 4), ("MA003", 3), ("MA004", 3), 
    ("EN001", 2), ("IT002", 4), ("SE104", 3), ("IS201", 3),
    ("CE118", 3), ("PE001", 1), ("SS001", 2), ("SS002", 2),
    ("IT003", 4), ("IT004", 4), ("MA005", 3)
]

def generate_csv(filename, num_students=250):
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["MSSV", "Khoa", "HoTen", "NgaySinh", "ThuTuHocKy", "TenHocKy", "MaMon", "TinChi", "GPA"])
        
        for i in range(num_students):
            mssv = 24520001 + i 
            khoa = 19
            name = f"{random.choice(first_names)} {random.choice(middle_names)} {random.choice(last_names)}"
            dob = f"{random.randint(1,28):02d}/{random.randint(1,12):02d}/2006"
            
            for ky_so in range(1, 4): 
                ten_hk = f"HK{ky_so} 2024-2025"
                # Cập nhật số lượng môn từ 6 đến 8 theo yêu cầu
                num_courses = random.randint(6, 8) 
                chosen_subjects = random.sample(subjects, num_courses)
                
                for ma_mon, tin_chi in chosen_subjects:
                    gpa = round(random.uniform(5.0, 10.0), 1)
                    writer.writerow([mssv, khoa, name, dob, ky_so, ten_hk, ma_mon, tin_chi, gpa])
                    
    print(f"✅ Đã tạo thành công file {filename} với {num_students} sinh viên (Mỗi kỳ 6-8 môn)!")

generate_csv("data.csv")
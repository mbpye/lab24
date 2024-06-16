#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

// Определим структуру для хранения данных о студенте
struct Student {
    char name[50];
    int id;
    double average_grade;
};

// Функция генерации случайных данных о студентах
void generateStudentData(const string& filename, int num_students) {
    ofstream file(filename, ios::binary);

    if (!file) {
        cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    vector<Student> students(num_students);
    for (int i = 0; i < num_students; ++i) {
        snprintf(students[i].name, sizeof(students[i].name), "Student%d", i + 1);
        students[i].id = i + 1;
        students[i].average_grade = rand() % 101 / 10.0; // случайная оценка от 0.0 до 10.0
    }

    file.write(reinterpret_cast<const char*>(students.data()), students.size() * sizeof(Student));
    file.close();
}

// Функция чтения данных из файла и вывод в виде таблицы
vector<Student> readStudentData(const string& filename) {
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "Не удалось открыть файл для чтения.\n";
        return {};
    }

    vector<Student> students;
    Student temp;

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        students.push_back(temp);
    }

    file.close();
    return students;
}

// Функция вывода данных о студентах в виде таблицы
void printStudents(const vector<Student>& students) {
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Average Grade" << "\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& student : students) {
        cout << setw(10) << student.id
            << setw(20) << student.name
            << setw(20) << fixed << setprecision(1) << student.average_grade
            << "\n";
    }
}

// Функция нахождения лучших студентов по среднему баллу
vector<Student> getTopStudents(const vector<Student>& students, int p) {
    vector<Student> top_students = students;
    sort(top_students.begin(), top_students.end(), [](const Student& a, const Student& b) {
        return b.average_grade < a.average_grade; // сортировка по убыванию
        });

    if (top_students.size() > p) {
        top_students.resize(p);
    }

    return top_students;
}

int main() {
    const string filename = "students.dat";
    const int num_students = 20;
    const int top_n = 5;

    // Генерация данных
    generateStudentData(filename, num_students);

    // Чтение данных
    vector<Student> students = readStudentData(filename);

    // Вывод данных в виде таблицы
    cout << "Список студентов:\n";
    printStudents(students);

    // Поиск и вывод лучших студентов
    vector<Student> top_students = getTopStudents(students, top_n);
    cout << "\nТоп " << top_n << " студентов по среднему баллу:\n";
    printStudents(top_students);

    return 0;
}
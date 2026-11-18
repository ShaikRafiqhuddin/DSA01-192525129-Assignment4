#include <iostream>
#include <string>

#ifdef NO_VIRTUAL
#define VBASE
#else
#define VBASE virtual
#endif

class Address {
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {
        std::cout << "Address(" << city << ") ";
    }
    ~Address() {
        std::cout << "~Address ";
    }
    std::string str() const {
        return city + "-" + std::to_string(pin);
    }
};

class Person {
protected:
    std::string name;
    int age;
    Address home;

public:
    Person(const std::string& n, int a, const std::string& c, int p)
        : name(n), age(a), home(c, p) {
        std::cout << "Person(" << name << ") ";
    }
    virtual ~Person() {
        std::cout << "~Person(" << name << ") ";
    }
};

class Course {
    std::string code;
    int credits;

public:
    Course(const std::string& co, int cr) : code(co), credits(cr) {
        std::cout << "Course(" << code << ") ";
    }
    ~Course() {
        std::cout << "~Course ";
    }
    std::string str() const {
        return code + "(" + std::to_string(credits) + "cr)";
    }
};

class Student : VBASE public Person {
protected:
    long long regNo;
    Course course;

public:
    Student(const std::string& n, int a, const std::string& c, int p,
            long long r, const std::string& co, int cr)
        : Person(n, a, c, p), regNo(r), course(co, cr) {
        std::cout << "Student(" << regNo << ") ";
    }
    ~Student() {
        std::cout << "~Student(" << regNo << ") ";
    }
};

class Staff : VBASE public Person {
protected:
    double salary;

public:
    Staff(const std::string& n, int a, const std::string& c, int p, double s)
        : Person(n, a, c, p), salary(s) {
        std::cout << "Staff(" << salary << ") ";
    }
    ~Staff() {
        std::cout << "~Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int a, const std::string& c, int p,
                      long long r, const std::string& co, int cr, double s)
        :
#ifndef NO_VIRTUAL
          Person(n, a, c, p),
#endif
          Student(n, a, c, p, r, co, cr),
          Staff(n, a, c, p, s) {
        std::cout << "TA ";
    }
    ~TeachingAssistant() {
        std::cout << "~TA ";
    }
};

int main() {
    std::cout << "--- construct Student ---\n";
    {
        Student s("Kavya", 19, "Salem", 636001, 192311001, "DSA0120", 4);
        std::cout << "\n--- destruct Student ---\n";
    }
    std::cout << "\n--- construct Staff ---\n";
    {
        Staff st("Rajan", 41, "Chennai", 600001, 55000);
        std::cout << "\n--- destruct Staff ---\n";
    }
    std::cout << "\n--- construct TeachingAssistant ---\n";
    {
        TeachingAssistant ta("Asha", 24, "Madurai", 625001, 192311045, "DSA0120", 4, 18000);
        std::cout << "\n--- destruct TeachingAssistant ---\n";
    }
#ifdef NO_VIRTUAL
    std::cout << "\n\nsizeof(TeachingAssistant) without virtual bases = "
              << sizeof(TeachingAssistant) << " bytes (two Person sub-objects)\n";
#else
    std::cout << "\n\nsizeof(TeachingAssistant) with virtual bases = "
              << sizeof(TeachingAssistant) << " bytes (one shared Person sub-object)\n";
#endif
    std::cout << '\n';
    return 0;
}

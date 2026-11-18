#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {
    }
    virtual ~Person() = default;
    void showPerson() const {
        std::cout << name << " (ID " << id << ", phone " << phone << ")";
    }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c,
                      const std::string& dept, double s)
        : Person(n, i, p), Student(n, i, p, prog, c), Staff(n, i, p, dept, s) {
        }

    void show() const {
        showPerson();
        std::cout << " | programme " << programme << ", CGPA " << cgpa
                  << " | dept " << department << ", salary " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    std::string fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double c, const std::string& f)
        : Person(n, i, p), Student(n, i, p, prog, c), fellowship(f) {
        }

    void show() const {
        showPerson();
        std::cout << " | programme " << programme << ", CGPA " << cgpa
                  << " | fellowship " << fellowship << '\n';
    }
};

struct StudentC {
    Person person;
    std::string programme;
    double cgpa;
    StudentC(const std::string& n, int i, const std::string& ph,
             const std::string& prog, double c)
        : person(n, i, ph), programme(prog), cgpa(c) {
        }
};

struct StaffC {
    Person person;
    std::string department;
    double salary;
    StaffC(const std::string& n, int i, const std::string& ph,
           const std::string& dept, double s)
        : person(n, i, ph), department(dept), salary(s) {
        }
};

struct TeachingAssistantC {
    StudentC student;
    StaffC staff;
    TeachingAssistantC(const std::string& n, int i, const std::string& ph,
                       const std::string& prog, double c,
                       const std::string& dept, double s)
        : student(n, i, ph, prog, c), staff(n, i, ph, dept, s) {
        }
};

int main() {
    TeachingAssistant ta("Asha", 5001, "98400-11111", "B.Tech CSE", 9.1, "CSE", 18000);
    std::cout << "TeachingAssistant: ";
    ta.show();

    ResearchScholar rs("Vikram", 5002, "98400-22222", "B.Tech CSE", 8.7, "CSIR-JRF");
    std::cout << "ResearchScholar:   ";
    rs.show();

    TeachingAssistantC tac("Asha", 5001, "98400-11111", "B.Tech CSE", 9.1, "CSE", 18000);

    std::cout << "\nsizeof(Person)               = " << sizeof(Person) << " bytes\n";
    std::cout << "sizeof(Student)              = " << sizeof(Student) << " bytes\n";
    std::cout << "sizeof(TeachingAssistant)    = " << sizeof(TeachingAssistant)
              << " bytes  (one shared Person sub-object)\n";
    std::cout << "sizeof(TeachingAssistantC)   = " << sizeof(TeachingAssistantC)
              << " bytes  (composition: two Person sub-objects)\n";
    return 0;
}

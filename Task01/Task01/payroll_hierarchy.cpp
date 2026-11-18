#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Employee {
protected:
    std::string name;
    int id;

public:
    Employee(const std::string& n, int i)
        : name(n), id(i) {
    }
    virtual ~Employee() = default;
    virtual double pay() const = 0;
    virtual std::string category() const = 0;
    int getId() const {
        return id;
    }
    const std::string& getName() const {
        return name;
    }
};

class SalariedEmployee : public Employee {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    SalariedEmployee(const std::string& n, int i, double b)
        : Employee(n, i), basic(b) {
    }
    double pay() const override {
        return basic + basic * DA_RATE;
    }
};

class Professor : public SalariedEmployee {
    double research;

public:
    Professor(const std::string& n, int i, double b, double r)
        : SalariedEmployee(n, i, b), research(r) {
        }
    double pay() const override {
        return basic + basic * DA_RATE + research;
    }
    std::string category() const override {
        return "Professor";
    }
};

class LabAssistant : public SalariedEmployee {
public:
    LabAssistant(const std::string& n, int i, double b)
        : SalariedEmployee(n, i, b) {
    }
    std::string category() const override {
        return "LabAssistant";
    }
};

class GuestFaculty : public Employee {
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Employee(n, i), hours(h), rate(r) {
        }
    double pay() const override {
        return hours * rate;
    }
    std::string category() const override {
        return "GuestFaculty";
    }
};

int main() {
    std::vector<Employee*> staff = {
        new Professor("Dr. Meera", 101, 80000, 15000),
        new LabAssistant("Ravi Kumar", 102, 30000),
        new GuestFaculty("Ms. Kiran", 103, 40, 1500)
    };

    std::cout << std::left << std::setw(6) << "ID" << std::setw(14) << "Name"
              << std::setw(14) << "Category" << std::right << std::setw(12) << "Pay" << '\n';
    std::cout << std::string(46, '-') << '\n';
    double total = 0;
    for (const Employee* e : staff) {
        std::cout << std::left << std::setw(6) << e->getId() << std::setw(14) << e->getName()
                  << std::setw(14) << e->category() << std::right << std::setw(12)
                  << std::fixed << std::setprecision(2) << e->pay() << '\n';
        total += e->pay();
    }
    std::cout << std::string(46, '-') << '\n';
    std::cout << "Total monthly payroll: " << total << '\n';

    for (Employee* e : staff) delete e;
    return 0;
}

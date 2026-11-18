#include <iostream>

struct Person {
    Person() {
        std::cout << "Person ";
    }
};

struct Student : Person {
    Student() {
        std::cout << "Student ";
    }
};

struct Staff : Person {
    Staff() {
        std::cout << "Staff ";
    }
};

struct TeachingAssistant : Student, Staff {
    TeachingAssistant() {
        std::cout << "TA\n";
    }
};

int main() {
    TeachingAssistant ta;
    return 0;
}

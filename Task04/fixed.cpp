#include <iostream>

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }
    virtual ~Account() {
        std::cout << "~Account\n";
    }
};

class SeniorAccount : public Account {
    double* history = new double[100];

public:
    double rate() const override {
        return 4.0;
    }
    ~SeniorAccount() override {
        delete[] history;
        std::cout << "~SeniorAccount (history released)\n";
    }
};

int main() {
    Account* accounts[2] = { new Account, new SeniorAccount };
    for (Account* a : accounts) std::cout << a->rate() << "\n";

    for (Account* a : accounts) delete a;

    SeniorAccount senior;
    Account& ref = senior;
    std::cout << "ref.rate() = " << ref.rate() << "\n";
    return 0;
}

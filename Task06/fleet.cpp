#include <iomanip>
#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool rented = false;
    int rentedDays = 0;

public:
    Vehicle(const std::string& r, double d)
        : regNo(r), dailyRate(d) {
    }
    virtual ~Vehicle() = default;

    virtual double charge(int days) const = 0;
    virtual std::string type() const = 0;

    bool isRented() const {
        return rented;
    }
    const std::string& reg() const {
        return regNo;
    }
    double rate() const {
        return dailyRate;
    }

    void rent(int days) {
        rented = true;
        rentedDays = days;
    }

    double giveBack(int actualDays) {
        double bill = charge(actualDays);
        if (actualDays > rentedDays)
            bill += (actualDays - rentedDays) * dailyRate * 1.5;
        rented = false;
        rentedDays = 0;
        return bill;
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& r, double d)
        : Vehicle(r, d) {
    }
    double charge(int days) const override {
        return days * dailyRate;
    }
    std::string type() const override {
        return "Bicycle";
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    std::string serviceDue;

public:
    MotorVehicle(const std::string& r, double d, double f, const std::string& sd)
        : Vehicle(r, d), fuelLevel(f), serviceDue(sd) {
        }
};

class TwoWheeler : public MotorVehicle {
    static constexpr double PETROL_PRICE = 110.0;

public:
    TwoWheeler(const std::string& r, double d, double f, const std::string& sd)
        : MotorVehicle(r, d, f, sd) {
        }
    double charge(int days) const override {
        double litresUsed = days * 1.5;
        return days * dailyRate + litresUsed * PETROL_PRICE;
    }
    std::string type() const override {
        return "TwoWheeler";
    }
};

class Car : public MotorVehicle {
protected:
    int seats;
    static constexpr double DIESEL_PRICE = 95.0;

public:
    Car(const std::string& r, double d, double f, const std::string& sd, int s)
        : MotorVehicle(r, d, f, sd), seats(s) {
        }
    double charge(int days) const override {
        double litresUsed = days * 4.0;
        return days * dailyRate + litresUsed * DIESEL_PRICE;
    }
    std::string type() const override {
        return "Car";
    }
};

class ElectricCar : public Car {
    double batteryKWh;
    double pricePerKWh;

public:
    ElectricCar(const std::string& r, double d, const std::string& sd, int s,
                double kwh, double pkwh)
        : Car(r, d, 100.0, sd, s), batteryKWh(kwh), pricePerKWh(pkwh) {
        }
    double charge(int days) const override {
        double kwhUsed = days * batteryKWh * 0.6;
        return days * dailyRate + kwhUsed * pricePerKWh;
    }
    std::string type() const override {
        return "ElectricCar";
    }
};

class ElectricBus : public Vehicle {
    double batteryKWh;
    double pricePerKWh;

public:
    ElectricBus(const std::string& r, double d, double kwh, double pkwh)
        : Vehicle(r, d), batteryKWh(kwh), pricePerKWh(pkwh) {
        }
    double charge(int days) const override {
        double kwhUsed = days * batteryKWh * 0.5;
        return days * dailyRate + kwhUsed * pricePerKWh;
    }
    std::string type() const override {
        return "ElectricBus";
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Vehicle* fleet[6] = {
        new Bicycle("TN01B1001", 100),
        new TwoWheeler("TN01T2002", 400, 100, "2026-12-15"),
        new Car("TN01C3003", 1500, 100, "2026-12-01", 5),
        new ElectricCar("TN01E4004", 2000, "2026-12-01", 5, 60, 8),
        nullptr,
        nullptr
    };
    int count = 4;

    std::cout << "== Rent each type ==\n";
    fleet[0]->rent(2);
    fleet[1]->rent(3);
    fleet[2]->rent(2);
    fleet[3]->rent(2);
    for (int i = 0; i < count; ++i)
        std::cout << fleet[i]->reg() << " (" << fleet[i]->type() << ") rented\n";

    std::cout << "\n== Return: Car returned 1 day late (late charge applies) ==\n";
    std::cout << "Bicycle    2 days: " << fleet[0]->giveBack(2) << '\n';
    std::cout << "TwoWheeler 3 days: " << fleet[1]->giveBack(3) << '\n';
    std::cout << "Car        3 days (booked 2): " << fleet[2]->giveBack(3) << '\n';
    std::cout << "ElectricCar 2 days: " << fleet[3]->giveBack(2) << '\n';

    std::cout << "\n== Add a new vehicle type WITHOUT changing existing classes ==\n";
    fleet[count++] = new ElectricBus("TN01EB5005", 5000, 200, 7);
    fleet[4]->rent(1);
    std::cout << "ElectricBus 1 day: " << fleet[4]->giveBack(1) << '\n';

    std::cout << "\n== Fleet list ==\n";
    for (int i = 0; i < count; ++i)
        std::cout << fleet[i]->reg() << "  " << fleet[i]->type()
                  << "  rate/day " << fleet[i]->rate()
                  << "  " << (fleet[i]->isRented() ? "RENTED" : "AVAILABLE") << '\n';

    for (int i = 0; i < count; ++i) delete fleet[i];
    return 0;
}

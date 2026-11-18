#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }

    int count() const {
        return n;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Cart direct;
    direct.add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "(a) direct object:       items=" << direct.count()
              << " total=" << direct.total() << '\n';

    Cart stackCart;
    Cart* ptr = &stackCart;
    ptr->add("Oil", 180);
    ptr->add("Soap", 45);
    std::cout << "(b) pointer with ->:     items=" << ptr->count()
              << " total=" << ptr->total() << '\n';

    Cart& ref = direct;
    ref.add("Sugar", 50);
    std::cout << "(c) reference alias:     items=" << ref.count()
              << " total=" << ref.total() << '\n';

    Cart* heap = new Cart;
    heap->add("Milk", 30).add("Bread", 40);
    std::cout << "(d) new/delete pointer:  items=" << heap->count()
              << " total=" << heap->total() << '\n';
    delete heap;

    Cart* active[3] = { new Cart, new Cart, new Cart };
    active[0]->add("Rice", 60).add("Dal", 120);
    active[1]->add("Oil", 180).add("Soap", 45).add("Sugar", 50);
    active[2]->add("Milk", 30);
    int best = 0;
    for (int i = 1; i < 3; ++i)
        if (active[i]->total() > active[best]->total()) best = i;
    std::cout << "\nActive carts (array of pointers): highest total is cart " << best
              << " with " << active[best]->total() << '\n';
    for (int i = 0; i < 3; ++i) delete active[i];
    return 0;
}

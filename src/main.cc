
#include <iostream>

#include "Food.h"

const int MAX = 20;

std::string GetName() {
    std::string First;
    std::cout << "Enter your first name: ";
    std::cin >> First;
    return First;
}

int main() {
    srand(time(0));
    std::string FirstName = GetName();
    std::string LastName = GetName();
    std::cout << "\n";
    std::string Items[MAX];
    int Quantity{};
    for (auto i : Items) {
        Quantity++;
    }
    Receipt receipt(FirstName,
                    LastName,
                    std::chrono::system_clock::now(),
                    std::chrono::system_clock::now(),
                    1,
                    Quantity,
                    Quantity * 1.838,
                    0);
    receipt.PrintReceipt();
    return 0;
}
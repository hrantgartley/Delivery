
#include <iostream>

#include "Food.h"

const int MAX = 20;

std::string GetFirst() {
    std::string First;
    std::cout << "Enter your first name: ";
    std::cin >> First;
    return First;
}

std::string GetLast() {
    std::string Last;
    std::cout << "Enter your last name: ";
    std::cin >> Last;
    return Last;
}

int Increment(int& Temp) {
    return Temp++;
}

int main() {
    srand(time(0));
    std::string FirstName = GetFirst();
    std::string LastName = GetLast();
    std::cout << "\n";
    std::string Items[MAX];
    int Quantity{};
    int Temp{1};
    for (auto i : Items) {
        Quantity = Increment(Temp);
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
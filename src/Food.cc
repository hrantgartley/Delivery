#include "Food.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

Receipt::Receipt(std::string first,
                 std::string last,
                 std::chrono::system_clock::time_point orderTime,
                 std::chrono::system_clock::time_point deliveryTime,
                 int orderNumber, int quantity, float total, float cashBack) {
    if (first.empty() || last.empty()) {
        throw std::invalid_argument("Names cannot be empty.");
    }
    if (orderNumber < 0) {
        throw std::invalid_argument("Order number cannot be negative.");
    }
    if (quantity < 0) {
        throw std::invalid_argument("Quantity cannot be negative.");
    }
    if (total < 0) {
        throw std::invalid_argument("Total cannot be negative.");
    }
    if (cashBack < 0) {
        throw std::invalid_argument("Cash back cannot be negative.");
    }
    First = first;
    Last = last;
    OrderTime = orderTime;
    DeliveryTime = deliveryTime;
    OrderNumber = orderNumber;
    Quantity = quantity;
    Total = total;
    TaxAmount = .08;
    CashBack = cashBack;
}

std::chrono::system_clock::time_point Receipt::CalculateOrderTime() {
    return std::chrono::system_clock::now();
}

std::chrono::system_clock::time_point Receipt::CalculateDeliveryTime() {
    std::chrono::minutes minOrderDelay(10);
    std::chrono::minutes maxOrderDelay(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minOrderDelay.count(), maxOrderDelay.count());
    std::chrono::minutes randomDelay(distribution(gen));

    std::chrono::system_clock::time_point deliveryTime = std::chrono::system_clock::now() + randomDelay;

    if (deliveryTime < std::chrono::system_clock::now())
        deliveryTime = std::chrono::system_clock::now() + minOrderDelay;

    return deliveryTime;
}

float Receipt::CalculateTotal() {
    if (TaxAmount > 1.0f) {
        throw new std::runtime_error("Invalid tax amount");
    }
    return (Total * TaxAmount) + Total;
}

std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& time) {
    auto timeT = std::chrono::system_clock::to_time_t(time);
    if (timeT == -1) {
        os << "Invalid time";
        return os;
    }
    auto timeInfo = std::localtime(&timeT);
    if (timeInfo == nullptr) {
        os << "Invalid time";
        return os;
    }
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    os << buffer;
    return os;
}

std::string Receipt::ReturnOrderInfo() {
    std::string OrderInfo{};
    OrderInfo = "Order Number: " + std::to_string(GenerateOrderNumber()) + "\n" +
                "Quantity: " + std::to_string(Quantity) + "\n" + "Total: " + std::to_string(Total);
    return OrderInfo;
}

std::string FormatTimePoint(const std::chrono::system_clock::time_point& timePoint) {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* tm = std::localtime(&time);
    if (tm == nullptr) {
        throw std::runtime_error("localtime failed");
    }

    char buffer[80];
    if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm) == 0) {
        throw std::runtime_error("strftime failed");
    }
    return std::string(buffer);
}

void Receipt::PrintReceipt() {
    std::cout << "Name: " << First << " " << Last << "\n";
    std::cout << "Order Time: " << OrderTime << "\n";
    std::cout << "Delivery Time: " << CalculateDeliveryTime() << "\n";
    std::cout << "Order Number: " << GenerateOrderNumber() << "\n";
    std::cout << "Quantity: " << Quantity << "\n";
    std::cout << "Total: " << Total << "\n";
}

int Receipt::GenerateOrderNumber() {
    srand(time(0));
    int orderNumber = rand() % 9999 + 69;
    return orderNumber / 4;
}

std::string Receipt::ReturnCustomerInfo() {
    return First + " " + Last;
}

std::string Receipt::ReturnDeliveryInfo() {
    std::chrono::system_clock::time_point deliveryTime = CalculateDeliveryTime();
    std::string formattedTime = FormatTimePoint(deliveryTime);
    return formattedTime;
}

std::string Receipt::ReturnPaymentInfo() {
    std::string PaymentInfo{};
    std::cout << "\n";
    PaymentInfo = "OrderNumber: " + std::to_string(OrderNumber) + "\nQuantity: " + std::to_string(Quantity) + "\nTotal: " +
                  std::to_string(Total) + " " + std::to_string(TaxAmount);
    return PaymentInfo;
}

std::string Receipt::GetCustomerInformation() const {
    std::string F = First;
    std::string L = Last;
    return F + " " + L;
}
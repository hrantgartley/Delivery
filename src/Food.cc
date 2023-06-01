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
    std::chrono::system_clock::time_point OrderTime = std::chrono::system_clock::now();
    return OrderTime;
}

std::chrono::system_clock::time_point Receipt::CalculateDeliveryTime() {
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

    std::chrono::minutes minOrderDelay(10);
    std::chrono::minutes maxOrderDelay(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minOrderDelay.count(), maxOrderDelay.count());
    std::chrono::minutes randomDelay(distribution(gen));

    std::chrono::system_clock::time_point deliveryTime = currentTime + randomDelay;

    return deliveryTime;
}

float Receipt::CalculateTotal() {
    return (Total * TaxAmount) + Total;
}

std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& time) {
    auto timeT = std::chrono::system_clock::to_time_t(time);
    auto timeInfo = std::localtime(&timeT);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    os << buffer;
    return os;
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
    int orderNumber = rand() % 999999 + 69;
    return orderNumber / 4;
}

std::string Receipt::ReturnCustomerInfo() {
    std::string CustomerInfo{};
    CustomerInfo = First + " " + Last;
    return CustomerInfo;
}

std::string Receipt::ReturnOrderInfo() {
    std::string OrderInfo{};
    OrderInfo = "Order Number: " + std::to_string(GenerateOrderNumber()) + "\n" + "Quantity: " + std::to_string(Quantity) + "\n" + "Total: " + std::to_string(Total);
    return OrderInfo;
}

std::string FormatTimePoint(const std::chrono::system_clock::time_point& timePoint) {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* tm = std::localtime(&time);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
    return std::string(buffer);
}

std::string Receipt::ReturnDeliveryInfo() {
    std::string DeliveryInfo{};
    std::chrono::system_clock::time_point deliveryTime = CalculateDeliveryTime();
    std::string formattedTime = FormatTimePoint(deliveryTime);
    DeliveryInfo = formattedTime;
    return DeliveryInfo;
}

std::string Receipt::ReturnPaymentInfo() {
    std::string PaymentInfo{};
    std::cout << "\n";
    PaymentInfo = "OrderNumber: " + std::to_string(OrderNumber) + "\nQuantity: " + std::to_string(Quantity) + "\nTotal: " +
                  std::to_string(Total) + " " + std::to_string(TaxAmount);
    return PaymentInfo;
}

#include <string>
#include <chrono>

class Receipt {
    private:
        std::string First{};
        std::string Last{};
        std::chrono::system_clock::time_point OrderTime{};
        std::chrono::system_clock::time_point DeliveryTime{};
        int OrderNumber{};
        int Quantity{};
        float Total{};
        float TaxAmount{};
        float CashBack{};
    public:
        Receipt(std::string, 
                std::string, 
                std::chrono::system_clock::time_point, 
                std::chrono::system_clock::time_point,
                int, int, float, float);
        std::chrono::system_clock::time_point CalculateOrderTime();
        std::chrono::system_clock::time_point CalculateDeliveryTime();
        float CalculateTotal();
        void PrintReceipt();
        friend std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& time);
        int GenerateOrderNumber();
        std::string ReturnCustomerInfo();
        std::string ReturnOrderInfo();
        std::string ReturnDeliveryInfo();
        std::string ReturnPaymentInfo();
};

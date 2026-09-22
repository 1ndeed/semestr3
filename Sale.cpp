#include "Sale.h"
#include "FormatUtils.h"

Sale::Sale(std::string medicineName, Date saleDate, int quantity, double totalPrice)
    : medicineName_(std::move(medicineName)),
    saleDate_(saleDate),
    quantity_(quantity),
    totalPrice_(totalPrice) {
}

const std::string& Sale::GetMedicineName() const { return medicineName_; }
const Date& Sale::GetSaleDate() const { return saleDate_; }
int Sale::GetQuantity() const { return quantity_; }
double Sale::GetTotalPrice() const { return totalPrice_; }

std::string Sale::GetInfo() const {
    return saleDate_.ToString() + ": " + medicineName_ +
        " x" + std::to_string(quantity_) +
        " = " + FormatUtils::FormatMoney(totalPrice_) + " руб.";
}

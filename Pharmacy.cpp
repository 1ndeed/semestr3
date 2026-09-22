#include "Pharmacy.h"
#include "FormatUtils.h"

Pharmacy::Pharmacy(std::string name) : name_(std::move(name)) {}

const std::string& Pharmacy::GetName() const { return name_; }

void Pharmacy::AddMedicine(std::shared_ptr<Medicine> medicine) {
    medicines_.push_back(std::move(medicine));
}

void Pharmacy::RegisterSale(const Sale& sale) {
    sales_.push_back(sale);
}

const std::vector<std::shared_ptr<Medicine>>& Pharmacy::GetAllMedicines() const {
    return medicines_;
}

std::shared_ptr<Medicine> Pharmacy::FindMedicineByName(const std::string& name) const {
    // Регистронезависимое сравнение с учётом UTF-8 (см. FormatUtils::EqualsIgnoreCase).
    for (const auto& medicine : medicines_) {
        if (FormatUtils::EqualsIgnoreCase(medicine->GetName(), name)) {
            return medicine;
        }
    }
    return nullptr;
}

int Pharmacy::PeriodLengthDays(SalesPeriod period) {
    switch (period) {
    case SalesPeriod::Week:  return 7;
    case SalesPeriod::Month: return 30;
    case SalesPeriod::Year:  return 365;
    }
    return 0;
}

bool Pharmacy::IsWithinPeriod(const Date& saleDate, const Date& asOf, SalesPeriod period) const {
    // Продажа учитывается, если она произошла не позже asOf и не
    // раньше, чем (asOf - длина периода) дней.
    long daysAgo = saleDate.DaysUntil(asOf); // asOf - saleDate
    return daysAgo >= 0 && daysAgo <= PeriodLengthDays(period);
}

std::vector<Sale> Pharmacy::GetSalesForPeriod(const std::string& medicineName,
    SalesPeriod period,
    const Date& asOf) const {
    std::vector<Sale> result;
    for (const auto& sale : sales_) {
        if (FormatUtils::EqualsIgnoreCase(sale.GetMedicineName(), medicineName) &&
            IsWithinPeriod(sale.GetSaleDate(), asOf, period)) {
            result.push_back(sale);
        }
    }
    return result;
}

int Pharmacy::GetTotalQuantitySold(const std::string& medicineName,
    SalesPeriod period,
    const Date& asOf) const {
    int total = 0;
    for (const auto& sale : GetSalesForPeriod(medicineName, period, asOf)) {
        total += sale.GetQuantity();
    }
    return total;
}

double Pharmacy::GetTotalRevenue(const std::string& medicineName,
    SalesPeriod period,
    const Date& asOf) const {
    double total = 0.0;
    for (const auto& sale : GetSalesForPeriod(medicineName, period, asOf)) {
        total += sale.GetTotalPrice();
    }
    return total;
}

std::vector<std::shared_ptr<Medicine>> Pharmacy::GetMedicinesForDisease(const std::string& disease) const {
    std::vector<std::shared_ptr<Medicine>> result;
    for (const auto& medicine : medicines_) {
        if (medicine->TreatsDisease(disease)) {
            result.push_back(medicine);
        }
    }
    return result;
}

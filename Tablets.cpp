#include "Tablets.h"
#include "FormatUtils.h"

Tablets::Tablets(std::string name,
    Date expirationDate,
    std::string annotation,
    double price,
    std::string manufacturer,
    std::vector<std::string> diseases,
    double dosageMg,
    int tabletsPerPack)
    : Medicine(std::move(name), expirationDate, std::move(annotation), price,
        std::move(manufacturer), std::move(diseases)),
    dosageMg_(dosageMg),
    tabletsPerPack_(tabletsPerPack) {
}

double Tablets::GetDosageMg() const { return dosageMg_; }
int Tablets::GetTabletsPerPack() const { return tabletsPerPack_; }

std::string Tablets::GetReleaseForm() const {
    return "Таблетки";
}

std::string Tablets::GetSpecificInfo() const {
    return "дозировка: " + FormatUtils::FormatDecimal(dosageMg_) +
        " мг, в упаковке: " + std::to_string(tabletsPerPack_) + " шт.";
}

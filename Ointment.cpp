#include "Ointment.h"
#include "FormatUtils.h"

Ointment::Ointment(std::string name,
    Date expirationDate,
    std::string annotation,
    double price,
    std::string manufacturer,
    std::vector<std::string> diseases,
    double massGrams)
    : Medicine(std::move(name), expirationDate, std::move(annotation), price,
        std::move(manufacturer), std::move(diseases)),
    massGrams_(massGrams) {
}

double Ointment::GetMassGrams() const { return massGrams_; }

std::string Ointment::GetReleaseForm() const {
    return "Мазь";
}

std::string Ointment::GetSpecificInfo() const {
    return "масса тюбика: " + FormatUtils::FormatDecimal(massGrams_) + " г";
}

#include "Injection.h"
#include "FormatUtils.h"

Injection::Injection(std::string name,
    Date expirationDate,
    std::string annotation,
    double price,
    std::string manufacturer,
    std::vector<std::string> diseases,
    double ampouleVolumeMl,
    int ampoulesPerPack)
    : Medicine(std::move(name), expirationDate, std::move(annotation), price,
        std::move(manufacturer), std::move(diseases)),
    ampouleVolumeMl_(ampouleVolumeMl),
    ampoulesPerPack_(ampoulesPerPack) {
}

double Injection::GetAmpouleVolumeMl() const { return ampouleVolumeMl_; }
int Injection::GetAmpoulesPerPack() const { return ampoulesPerPack_; }

std::string Injection::GetReleaseForm() const {
    return "Ампулы (раствор для инъекций)";
}

std::string Injection::GetSpecificInfo() const {
    return "объём ампулы: " + FormatUtils::FormatDecimal(ampouleVolumeMl_) +
        " мл, в упаковке: " + std::to_string(ampoulesPerPack_) + " шт.";
}

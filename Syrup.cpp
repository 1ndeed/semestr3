#include "Syrup.h"
#include "FormatUtils.h"

Syrup::Syrup(std::string name,
    Date expirationDate,
    std::string annotation,
    double price,
    std::string manufacturer,
    std::vector<std::string> diseases,
    double volumeMl)
    : Medicine(std::move(name), expirationDate, std::move(annotation), price,
        std::move(manufacturer), std::move(diseases)),
    volumeMl_(volumeMl) {
}

double Syrup::GetVolumeMl() const { return volumeMl_; }

std::string Syrup::GetReleaseForm() const {
    return "Сироп";
}

std::string Syrup::GetSpecificInfo() const {
    return "объём флакона: " + FormatUtils::FormatDecimal(volumeMl_) + " мл";
}

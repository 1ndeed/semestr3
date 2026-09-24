#include "Medicine.h"
#include "FormatUtils.h"

Medicine::Medicine(std::string name,
    Date expirationDate,
    std::string annotation,
    double price,
    std::string manufacturer,
    std::vector<std::string> diseases)
    : name_(std::move(name)),
    expirationDate_(expirationDate),
    annotation_(std::move(annotation)),
    price_(price),
    manufacturer_(std::move(manufacturer)),
    diseases_(std::move(diseases)) {
}

const std::string& Medicine::GetName() const { return name_; }
const Date& Medicine::GetExpirationDate() const { return expirationDate_; }
const std::string& Medicine::GetAnnotation() const { return annotation_; }
double Medicine::GetPrice() const { return price_; }
const std::string& Medicine::GetManufacturer() const { return manufacturer_; }
const std::vector<std::string>& Medicine::GetDiseases() const { return diseases_; }

bool Medicine::IsExpired(const Date& asOf) const {
    return expirationDate_ < asOf;
}

bool Medicine::TreatsDisease(const std::string& disease) const {
    for (const auto& d : diseases_) {
        if (FormatUtils::EqualsIgnoreCase(d, disease)) {
            return true;
        }
    }
    return false;
}

std::string Medicine::GetInfo() const {
    // Формируем список болезней через запятую, с заглушкой, если у
    // лекарства не указано ни одной болезни.
    std::string diseasesList;
    for (size_t i = 0; i < diseases_.size(); ++i) {
        if (i > 0) diseasesList += ", ";
        diseasesList += diseases_[i];
    }
    if (diseasesList.empty()) {
        diseasesList = "не указано";
    }

    return name_ +
        " [" + GetReleaseForm() + "]" +
        " | цена: " + FormatUtils::FormatMoney(price_) + " руб." +
        " | изготовитель: " + manufacturer_ +
        " | срок годности до: " + expirationDate_.ToString() +
        " | применяется при: " + diseasesList +
        " | " + GetSpecificInfo() +
        " | аннотация: " + annotation_;
}

#include "Date.h"
#include <stdexcept>
#include <cstdlib>

namespace {

    /** @brief Возвращает true, если @p year - високосный год по григорианскому календарю. */
    bool IsLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    /**
     * @brief Возвращает количество дней в указанном месяце указанного
     *        года (учитывает високосные годы для февраля).
     */
    int DaysInMonth(int year, int month) {
        static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && IsLeapYear(year)) {
            return 29;
        }
        return days[month - 1];
    }

    /**
     * @brief Переводит гражданскую (григорианскую) дату в количество
     *        дней относительно эпохи 1970-01-01 по алгоритму Говарда
     *        Хиннанта (days_from_civil). Не зависит от <ctime> или
     *        локали и корректно работает для любых разумных дат, не
     *        обращаясь к потокам ввода-вывода.
     * @param y Календарный год.
     * @param m Месяц, 1-12.
     * @param d День месяца.
     * @return Знаковое количество дней относительно 1970-01-01
     *         (отрицательное для более ранних дат).
     */
    long DaysFromCivil(int y, unsigned m, unsigned d) {
        y -= m <= 2;
        const long era = (y >= 0 ? y : y - 399) / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);          // [0, 399]
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;         // [0, 146096]
        return era * 146097 + static_cast<long>(doe) - 719468;
    }

} // namespace

void Date::Validate(int year, int month, int day) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Date: месяц должен быть в диапазоне 1..12");
    }
    if (day < 1 || day > DaysInMonth(year, month)) {
        throw std::invalid_argument("Date: некорректный день для указанного месяца/года");
    }
}

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {
    Validate(year_, month_, day_);
}

Date Date::Parse(const std::string& isoDate) {
    // Ожидаемый формат: "ГГГГ-ММ-ДД" (ровно 10 символов, дефисы на
    // позициях 4 и 7).
    if (isoDate.size() != 10 || isoDate[4] != '-' || isoDate[7] != '-') {
        throw std::invalid_argument("Date::Parse: ожидается формат ГГГГ-ММ-ДД");
    }
    for (size_t i = 0; i < isoDate.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (isoDate[i] < '0' || isoDate[i] > '9') {
            throw std::invalid_argument("Date::Parse: ожидается формат ГГГГ-ММ-ДД");
        }
    }
    const int year = std::atoi(isoDate.substr(0, 4).c_str());
    const int month = std::atoi(isoDate.substr(5, 2).c_str());
    const int day = std::atoi(isoDate.substr(8, 2).c_str());
    return Date(year, month, day);
}

int Date::GetYear() const { return year_; }
int Date::GetMonth() const { return month_; }
int Date::GetDay() const { return day_; }

std::string Date::ToString() const {
    auto pad2 = [](int value) {
        std::string s = std::to_string(value);
        if (s.size() < 2) s = "0" + s;
        return s;
        };
    return std::to_string(year_) + "-" + pad2(month_) + "-" + pad2(day_);
}

long Date::ToDayNumber() const {
    return DaysFromCivil(year_, static_cast<unsigned>(month_), static_cast<unsigned>(day_));
}

long Date::DaysUntil(const Date& other) const {
    return other.ToDayNumber() - ToDayNumber();
}

bool Date::operator==(const Date& other) const {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}
bool Date::operator!=(const Date& other) const { return !(*this == other); }
bool Date::operator<(const Date& other) const { return ToDayNumber() < other.ToDayNumber(); }
bool Date::operator<=(const Date& other) const { return ToDayNumber() <= other.ToDayNumber(); }
bool Date::operator>(const Date& other) const { return ToDayNumber() > other.ToDayNumber(); }
bool Date::operator>=(const Date& other) const { return ToDayNumber() >= other.ToDayNumber(); }

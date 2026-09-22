#include "FormatUtils.h"
#include <cctype>
#include <cmath>

namespace {

    /**
     * @brief Таблица "заглавная буква -> строчная буква" для русского
     *        алфавита (плюс Ё/ё). Файл собирается с флагом /utf-8,
     *        поэтому каждая русская буква в исходном коде - это уже
     *        готовая строка из тех самых байт UTF-8, которыми она
     *        записана в тексте программы. Так не нужно вручную
     *        разбираться, как устроена кодировка UTF-8 изнутри - буквы
     *        просто сравниваются друг с другом, как обычный текст.
     */
    const std::pair<std::string, std::string> kCyrillicUpperToLower[] = {
        {"А", "а"}, {"Б", "б"}, {"В", "в"}, {"Г", "г"}, {"Д", "д"},
        {"Е", "е"}, {"Ж", "ж"}, {"З", "з"}, {"И", "и"}, {"Й", "й"},
        {"К", "к"}, {"Л", "л"}, {"М", "м"}, {"Н", "н"}, {"О", "о"},
        {"П", "п"}, {"Р", "р"}, {"С", "с"}, {"Т", "т"}, {"У", "у"},
        {"Ф", "ф"}, {"Х", "х"}, {"Ц", "ц"}, {"Ч", "ч"}, {"Ш", "ш"},
        {"Щ", "щ"}, {"Ъ", "ъ"}, {"Ы", "ы"}, {"Ь", "ь"}, {"Э", "э"},
        {"Ю", "ю"}, {"Я", "я"}, {"Ё", "ё"},
    };

    /**
     * @brief Ищет в @p s, начиная с позиции @p pos, одну из заглавных
     *        русских букв из таблицы kCyrillicUpperToLower.
     * @param s   Строка, в которой выполняется поиск.
     * @param pos Позиция, с которой нужно проверить совпадение.
     * @return Указатель на подходящую строку нижнего регистра из
     *         таблицы, либо nullptr, если совпадений не найдено (буква
     *         не заглавная русская - например, уже строчная, латинская
     *         или знак препинания).
     */
    const std::string* FindCyrillicLowerCase(const std::string& s, size_t pos) {
        for (const auto& pair : kCyrillicUpperToLower) {
            const std::string& upper = pair.first;
            if (s.compare(pos, upper.size(), upper) == 0) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    /**
     * @brief Приводит строку в UTF-8 к нижнему регистру: латинские
     *        буквы - через стандартную std::tolower, русские буквы -
     *        через таблицу замен kCyrillicUpperToLower (каждая
     *        заглавная русская буква ищется в строке как есть и
     *        заменяется на её строчный вариант). Символы, для которых
     *        замены нет, копируются без изменений.
     * @param s Строка для приведения к нижнему регистру.
     * @return Строка @p s в нижнем регистре.
     */
    std::string ToLower(const std::string& s) {
        std::string result;
        result.reserve(s.size());

        size_t pos = 0;
        while (pos < s.size()) {
            unsigned char byte = static_cast<unsigned char>(s[pos]);

            if (byte < 0x80) {
                // Латинская буква, цифра, пробел, знак препинания...
                result += static_cast<char>(std::tolower(byte));
                ++pos;
                continue;
            }

            if (const std::string* lower = FindCyrillicLowerCase(s, pos)) {
                result += *lower;
                pos += lower->size();
            }
            else {
                // Уже строчная русская буква либо другой символ - замены
                // не требуется, копируем как есть.
                result += static_cast<char>(byte);
                ++pos;
            }
        }

        return result;
    }

}

namespace FormatUtils {

    std::string FormatDecimal(double value) {
        bool negative = value < 0.0;
        if (negative) {
            value = -value;
        }
        long long hundredths = static_cast<long long>(std::floor(value * 100.0 + 0.5));
        long long whole = hundredths / 100;
        long long frac = hundredths % 100;

        std::string result = std::to_string(whole) + "." +
            (frac < 10 ? "0" : "") + std::to_string(frac);
        if (negative && hundredths != 0) {
            result = "-" + result;
        }
        return result;
    }

    std::string FormatMoney(double value) {
        return FormatDecimal(value);
    }

    bool EqualsIgnoreCase(const std::string& a, const std::string& b) {
        return ToLower(a) == ToLower(b);
    }

}

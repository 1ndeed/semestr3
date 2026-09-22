//
// main.cpp
// Демонстрационная консольная программа для варианта задания "Аптека".
//
// Задание 1 (общее, единое для всех вариантов): создать коллекцию
// объектов базового типа, заполнить её объектами типов-наследников,
// проитерировать её как коллекцию базового класса и вывести информацию
// о каждом объекте в std::cout.
//
// Задания варианта "Аптека":
//   1) Выдавать данные о лекарствах.
//   2) Выдавать информацию о продажах покупателям за неделю (месяц, год)
//      данного лекарства.
//   3) Выдавать список лекарств, применяемых при выбранной болезни.
//
// Структура файла: сначала объявления (прототипы) всех вспомогательных
// функций с их документацией, затем main(), и уже после main() -
// реализации (тела) этих функций в том же порядке.
//
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX // без этого Windows.h объявляет макросы min/max, которые
                 // ломают std::numeric_limits<...>::max() ниже по файлу
#include <Windows.h>
#endif

#include "AptekaLib.h"

namespace {

    /**
     * @brief Пункты главного меню. Значения соответствуют тому, что
     *        пользователь вводит с клавиатуры. PrintMenu() выводит эти
     *        же числа на экран через приведение значений enum к int
     *        (см. static_cast<int>(...) в реализации), а не отдельными
     *        захардкоженными цифрами в строке - так текст меню и код
     *        обработки выбора не могут разойтись между собой.
     */
    enum class MainMenuChoice {
        Exit = 0,                     ///< "0 - Выход"
        ShowMedicines = 1,             ///< "1 - Данные о лекарствах" (задание 1)
        ShowSalesReport = 2,           ///< "2 - Продажи..." (задание 2)
        ShowMedicinesForDisease = 3,   ///< "3 - Лекарства для болезни" (задание 3)
    };

    /**
     * @brief Пункты подменю выбора отчётного периода (см. AskPeriod()).
     *        Как и MainMenuChoice, значения используются и в switch, и
     *        при печати текста подсказки - одно и то же enum-значение,
     *        а не два независимых магических числа.
     */
    enum class PeriodMenuChoice {
        Week = 1,   ///< "1 - неделя"
        Month = 2,  ///< "2 - месяц"
        Year = 3,   ///< "3 - год"
    };

#ifdef _WIN32
    /**
     * @brief Переключает кодовые страницы ввода/вывода консоли Windows
     *        в UTF-8. Проект собирается с флагом /utf-8, поэтому без
     *        этого консоль печатала бы русский текст в виде кракозябр.
     *        На платформах, отличных от Windows, функция не вызывается.
     */
    void EnableUtf8Console();
#endif

    /** @brief Печатает горизонтальную разделительную линию в std::cout. */
    void PrintDivider();

    /**
     * @brief Возвращает зафиксированную "текущую" дату демо-программы.
     *        Захардкожена (а не взята из системных часов), чтобы отчёты
     *        за неделю/месяц/год были воспроизводимы при каждом запуске.
     * @return Опорная дата, используемая во всей демонстрации.
     */
    Date Today();

    /**
     * @brief Формирует демонстрационную коллекцию лекарств, реализуя
     *        общее требование задания 1: коллекцию БАЗОВОГО типа
     *        (Medicine), заполненную объектами типов-наследников
     *        (Tablets/Syrup/Ointment/Injection).
     * @return Вектор умных указателей на Medicine, владеющий шестью
     *         демонстрационными лекарствами.
     */
    std::vector<std::shared_ptr<Medicine>> CreateDemoMedicines();

    /**
     * @brief Формирует демонстрационную аптеку: регистрирует в ней все
     *        лекарства из @p medicines и заполняет небольшой пример
     *        журнала продаж, чтобы отчёты за неделю/месяц/год
     *        (задание 2) было на чём показать.
     * @param medicines Лекарства для регистрации в аптеке.
     * @return Экземпляр Pharmacy, готовый к использованию в демо-меню.
     */
    Pharmacy CreateDemoPharmacy(const std::vector<std::shared_ptr<Medicine>>& medicines);

    // ---- Задание 1: коллекция базового типа + полиморфный вывод ----

    /**
     * @brief Проходит коллекцию лекарств через указатели базового
     *        класса (Medicine) и печатает информацию о каждом элементе
     *        в std::cout. GetInfo()/GetReleaseForm() виртуальные,
     *        поэтому вызывается реализация конкретного класса-наследника,
     *        хотя статический тип каждого элемента - "указатель на
     *        Medicine": это и есть требование задания 1 о полиморфном
     *        обходе коллекции.
     * @param medicines Коллекция для вывода.
     */
    void PrintAllMedicinesPolymorphically(const std::vector<std::shared_ptr<Medicine>>& medicines);

    // ---- Задание 2: продажи за период ----

    /**
     * @brief Запрашивает у пользователя через консоль выбор отчётного периода.
     * @return SalesPeriod::Month или SalesPeriod::Year для
     *         соответствующего ввода, SalesPeriod::Week для любого
     *         другого значения (включая "1").
     */
    SalesPeriod AskPeriod();

    /**
     * @brief Возвращает название периода на русском языке для
     *        подстановки в заголовок отчёта о продажах.
     * @param period Период для именования.
     * @return "неделю" / "месяц" / "год", либо "период" как запасной вариант.
     */
    std::string PeriodName(SalesPeriod period);

    /**
     * @brief Обработчик пункта меню для задания 2: считывает с консоли
     *        название лекарства и период, затем печатает найденные
     *        продажи, суммарное проданное количество и суммарную выручку.
     * @param pharmacy Аптека, к которой выполняется запрос.
     */
    void ShowSalesReport(const Pharmacy& pharmacy);

    // ---- Задание 3: лекарства для выбранной болезни ----

    /**
     * @brief Обработчик пункта меню для задания 3: считывает с консоли
     *        название болезни/недуга и печатает все лекарства,
     *        применяемые для её лечения.
     * @param pharmacy Аптека, к которой выполняется запрос.
     */
    void ShowMedicinesForDisease(const Pharmacy& pharmacy);

    /** @brief Печатает в std::cout пункты главного меню. */
    void PrintMenu();

} // namespace

/**
 * @brief Точка входа программы. Формирует демонстрационную коллекцию
 *        лекарств и аптеку, печатает полиморфный обход коллекции,
 *        требуемый заданием 1, затем запускает интерактивное текстовое
 *        меню, реализующее три задания варианта "Аптека".
 * @return 0 при нормальном завершении.
 */
int main() {
#ifdef _WIN32
    EnableUtf8Console();
#endif

    // Требование задания 1: коллекция объектов БАЗОВОГО типа,
    // заполненная объектами типов-наследников. Ни medicines, ни
    // pharmacy не переприсваиваются ниже по функции - обе константы.
    const std::vector<std::shared_ptr<Medicine>> medicines = CreateDemoMedicines();
    const Pharmacy pharmacy = CreateDemoPharmacy(medicines);

    std::cout << "=== " << pharmacy.GetName() << " ===\n";

    // Сразу показываем полиморфный обход коллекции (демонстрация
    // "общей" формулировки задания 1).
    PrintAllMedicinesPolymorphically(medicines);

    bool running = true;
    while (running) {
        PrintMenu();
        int choice = -1;
        if (!(std::cin >> choice)) {
            break; // конец ввода (например, при перенаправлении из файла)
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (static_cast<MainMenuChoice>(choice)) {
        case MainMenuChoice::ShowMedicines:
            PrintAllMedicinesPolymorphically(medicines);
            break;
        case MainMenuChoice::ShowSalesReport:
            ShowSalesReport(pharmacy);
            break;
        case MainMenuChoice::ShowMedicinesForDisease:
            ShowMedicinesForDisease(pharmacy);
            break;
        case MainMenuChoice::Exit:
            running = false;
            break;
        default:
            std::cout << "Неизвестный пункт меню.\n";
            break;
        }
    }

    std::cout << "Работа программы завершена.\n";
    return 0;
}

// ============================================================================
// Реализации функций, объявленных выше (см. их документацию у прототипов).
// ============================================================================

namespace {

#ifdef _WIN32
    void EnableUtf8Console() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    }
#endif

    void PrintDivider() {
        std::cout << "------------------------------------------------------------\n";
    }

    Date Today() {
        return Date(2026, 9, 22);
    }

    std::vector<std::shared_ptr<Medicine>> CreateDemoMedicines() {
        std::vector<std::shared_ptr<Medicine>> medicines;

        medicines.push_back(std::make_shared<Tablets>(
            "Парацетамол",
            Date(2027, 5, 1),
            "Жаропонижающее и обезболивающее средство.",
            45.50,
            "Фармстандарт",
            std::vector<std::string>{"простуда", "головная боль", "повышенная температура"},
            500.0,
            20));

        medicines.push_back(std::make_shared<Tablets>(
            "Ибупрофен",
            Date(2027, 3, 10),
            "Нестероидное противовоспалительное средство.",
            60.00,
            "Реафарм",
            std::vector<std::string>{"головная боль", "повышенная температура", "боль в мышцах"},
            200.0,
            10));

        medicines.push_back(std::make_shared<Syrup>(
            "Доктор МОМ",
            Date(2026, 12, 1),
            "Растительный сироп от кашля.",
            210.00,
            "Юник Фармасьютикал",
            std::vector<std::string>{"кашель", "простуда"},
            100.0));

        medicines.push_back(std::make_shared<Syrup>(
            "Пертуссин",
            Date(2026, 10, 5),
            "Отхаркивающее средство на основе экстракта чабреца.",
            85.30,
            "Флора Кавказа",
            std::vector<std::string>{"кашель"},
            125.0));

        medicines.push_back(std::make_shared<Ointment>(
            "Финалгон",
            Date(2027, 1, 15),
            "Разогревающая мазь для наружного применения.",
            320.75,
            "Берингер Ингельхайм",
            std::vector<std::string>{"боль в мышцах", "боль в суставах"},
            20.0));

        medicines.push_back(std::make_shared<Injection>(
            "Диклофенак",
            Date(2026, 11, 20),
            "Противовоспалительное средство для внутримышечного введения.",
            150.00,
            "Хемофарм",
            std::vector<std::string>{"боль в суставах", "воспаление"},
            3.0,
            5));

        return medicines;
    }

    Pharmacy CreateDemoPharmacy(const std::vector<std::shared_ptr<Medicine>>& medicines) {
        Pharmacy pharmacy("Аптека №1 \"Здоровье\"");
        for (const auto& medicine : medicines) {
            pharmacy.AddMedicine(medicine);
        }

        // Демонстрационный журнал продаж (даты отсчитаны от Today() = 2026-09-16).
        pharmacy.RegisterSale(Sale("Парацетамол", Date(2026, 9, 14), 3, 136.50));   // 2 дня назад  -> неделя
        pharmacy.RegisterSale(Sale("Парацетамол", Date(2026, 8, 25), 5, 227.50));   // 22 дня назад -> месяц
        pharmacy.RegisterSale(Sale("Парацетамол", Date(2026, 1, 10), 2, 91.00));    // ~249 дней    -> год
        pharmacy.RegisterSale(Sale("Парацетамол", Date(2024, 5, 1), 1, 45.50));     // старая продажа, вне года
        pharmacy.RegisterSale(Sale("Доктор МОМ", Date(2026, 9, 10), 1, 210.00));    // 6 дней назад -> неделя
        pharmacy.RegisterSale(Sale("Ибупрофен", Date(2026, 9, 15), 4, 240.00));     // 1 день назад -> неделя

        return pharmacy;
    }

    void PrintAllMedicinesPolymorphically(const std::vector<std::shared_ptr<Medicine>>& medicines) {
        PrintDivider();
        std::cout << "Задание 1. Данные о лекарствах (полиморфный обход коллекции базового типа Medicine):\n";
        PrintDivider();
        for (const std::shared_ptr<Medicine>& medicine : medicines) {
            std::cout << medicine->GetInfo() << "\n";
        }
    }

    SalesPeriod AskPeriod() {
        std::cout << "Выберите период ("
            << static_cast<int>(PeriodMenuChoice::Week) << " - неделя, "
            << static_cast<int>(PeriodMenuChoice::Month) << " - месяц, "
            << static_cast<int>(PeriodMenuChoice::Year) << " - год): ";
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (static_cast<PeriodMenuChoice>(choice)) {
        case PeriodMenuChoice::Month: return SalesPeriod::Month;
        case PeriodMenuChoice::Year:  return SalesPeriod::Year;
        default: return SalesPeriod::Week;
        }
    }

    std::string PeriodName(SalesPeriod period) {
        switch (period) {
        case SalesPeriod::Week:  return "неделю";
        case SalesPeriod::Month: return "месяц";
        case SalesPeriod::Year:  return "год";
        }
        return "период";
    }

    void ShowSalesReport(const Pharmacy& pharmacy) {
        std::cout << "Введите название лекарства: ";
        std::string name;
        std::getline(std::cin, name);

        if (!pharmacy.FindMedicineByName(name)) {
            std::cout << "Лекарство \"" << name << "\" не найдено в справочнике.\n";
            return;
        }

        const SalesPeriod period = AskPeriod();
        const Date today = Today();

        const auto sales = pharmacy.GetSalesForPeriod(name, period, today);
        PrintDivider();
        std::cout << "Продажи \"" << name << "\" за " << PeriodName(period)
            << " (по состоянию на " << today.ToString() << "):\n";
        if (sales.empty()) {
            std::cout << "  Продаж за указанный период не найдено.\n";
        }
        else {
            for (const auto& sale : sales) {
                std::cout << "  " << sale.GetInfo() << "\n";
            }
        }
        std::cout << "Итого продано: " << pharmacy.GetTotalQuantitySold(name, period, today)
            << " шт. на сумму " << FormatUtils::FormatMoney(pharmacy.GetTotalRevenue(name, period, today))
            << " руб.\n";
    }

    void ShowMedicinesForDisease(const Pharmacy& pharmacy) {
        std::cout << "Введите название болезни/недуга (например: кашель, простуда, головная боль): ";
        std::string disease;
        std::getline(std::cin, disease);

        const auto found = pharmacy.GetMedicinesForDisease(disease);
        PrintDivider();
        std::cout << "Лекарства, применяемые при \"" << disease << "\":\n";
        if (found.empty()) {
            std::cout << "  Ничего не найдено.\n";
        }
        else {
            for (const auto& medicine : found) {
                std::cout << "  " << medicine->GetInfo() << "\n";
            }
        }
    }

    void PrintMenu() {
        PrintDivider();
        std::cout << static_cast<int>(MainMenuChoice::ShowMedicines)
            << " - Данные о лекарствах (Задание 1)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowSalesReport)
            << " - Продажи по лекарству за неделю/месяц/год (Задание 2)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowMedicinesForDisease)
            << " - Лекарства для выбранной болезни (Задание 3)\n";
        std::cout << static_cast<int>(MainMenuChoice::Exit) << " - Выход\n";
        std::cout << "Ваш выбор: ";
    }

} // namespace

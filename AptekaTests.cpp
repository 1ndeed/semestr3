//
// AptekaTests.cpp
// Все модульные тесты проекта (30 штук) в одном файле, на встроенном в
// Visual Studio фреймворке Microsoft CppUnitTest:
//   - TEST_CLASS(DateTests)     - класс Date;
//   - TEST_CLASS(MedicineTests) - базовый класс Medicine и классы-
//                                 наследники Tablets/Syrup/Ointment/Injection;
//   - TEST_CLASS(PharmacyTests) - класс Pharmacy, все три задания
//                                 варианта "Аптека".
//
#include "CppUnitTest.h"
#include "AptekaLib.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AptekaTests
{
    // ==== Тесты класса Date ====

    TEST_CLASS(DateTests)
    {
    public:
        /** @brief Parse() корректно извлекает год/месяц/день из допустимой строки. */
        TEST_METHOD(Parse_ValidIsoString_ReturnsCorrectComponents)
        {
            Date d = Date::Parse("2026-09-16");
            Assert::AreEqual(2026, d.GetYear());
            Assert::AreEqual(9, d.GetMonth());
            Assert::AreEqual(16, d.GetDay());
        }

        /** @brief Parse() отклоняет строку, не соответствующую формату ГГГГ-ММ-ДД. */
        TEST_METHOD(Parse_WrongFormat_ThrowsInvalidArgument)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                Date::Parse("16-09-2026");
                });
        }

        /** @brief Конструктор отклоняет месяц вне диапазона 1..12. */
        TEST_METHOD(Constructor_InvalidMonth_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                Date invalid(2026, 13, 1);
                (void)invalid;
                });
        }

        /** @brief Конструктор отклоняет день, которого не существует в указанном месяце. */
        TEST_METHOD(Constructor_InvalidDayForMonth_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                Date invalid(2026, 2, 30); // 2026 - не високосный год, в феврале 28 дней
                (void)invalid;
                });
        }

        /** @brief DaysUntil() возвращает ноль при сравнении даты с самой собой. */
        TEST_METHOD(DaysUntil_SameDate_ReturnsZero)
        {
            Date d(2026, 9, 16);
            Assert::AreEqual(0L, d.DaysUntil(d));
        }

        /** @brief DaysUntil() возвращает 7 для двух дат, отстоящих ровно на неделю. */
        TEST_METHOD(DaysUntil_OneWeekLater_ReturnsSeven)
        {
            Date start(2026, 9, 9);
            Date end(2026, 9, 16);
            Assert::AreEqual(7L, start.DaysUntil(end));
        }

        /** @brief DaysUntil() корректно работает, когда интервал пересекает границу года. */
        TEST_METHOD(DaysUntil_AcrossYearBoundary_IsCorrect)
        {
            Date start(2025, 12, 30);
            Date end(2026, 1, 2);
            Assert::AreEqual(3L, start.DaysUntil(end));
        }

        /** @brief Шесть операторов сравнения/равенства работают как ожидается. */
        TEST_METHOD(ComparisonOperators_WorkAsExpected)
        {
            Date a(2026, 1, 1);
            Date b(2026, 1, 2);
            Assert::IsTrue(a < b);
            Assert::IsTrue(b > a);
            Assert::IsTrue(a != b);
            Assert::IsFalse(a == b);
            Assert::IsTrue(a == Date(2026, 1, 1));
        }

        /** @brief ToString() дополняет месяц и день ведущим нулём. */
        TEST_METHOD(ToString_FormatsWithLeadingZeros)
        {
            Date d(2026, 3, 5);
            Assert::AreEqual(std::string("2026-03-05"), d.ToString());
        }

        /** @brief 29 февраля принимается в високосном году. */
        TEST_METHOD(LeapYear_February29_IsValid)
        {
            Date d(2028, 2, 29); // 2028 - високосный год
            Assert::AreEqual(29, d.GetDay());
        }
    };

    // ==== Тесты базового класса Medicine и классов-наследников ====

    TEST_CLASS(MedicineTests)
    {
    public:
        /** @brief Tablets::GetReleaseForm() возвращает метку "Таблетки". */
        TEST_METHOD(Tablets_GetReleaseForm_ReturnsTabletki)
        {
            Tablets t("Парацетамол", Date(2027, 1, 1), "аннотация", 45.50, "Фармстандарт",
                std::vector<std::string>{"простуда"}, 500.0, 20);
            Assert::AreEqual(std::string("Таблетки"), t.GetReleaseForm());
        }

        /** @brief Геттеры Tablets возвращают именно те значения, что были переданы конструктору. */
        TEST_METHOD(Tablets_Getters_ReturnConstructorValues)
        {
            Tablets t("Ибупрофен", Date(2027, 1, 1), "аннотация", 60.0, "Реафарм",
                std::vector<std::string>{"головная боль"}, 200.0, 10);
            Assert::AreEqual(200.0, t.GetDosageMg(), 0.0001);
            Assert::AreEqual(10, t.GetTabletsPerPack());
        }

        /** @brief Syrup::GetReleaseForm() и GetVolumeMl() возвращают верные значения. */
        TEST_METHOD(Syrup_GetReleaseForm_ReturnsSirop)
        {
            Syrup s("Доктор МОМ", Date(2027, 1, 1), "аннотация", 210.0, "Юник",
                std::vector<std::string>{"кашель"}, 100.0);
            Assert::AreEqual(std::string("Сироп"), s.GetReleaseForm());
            Assert::AreEqual(100.0, s.GetVolumeMl(), 0.0001);
        }

        /** @brief Ointment::GetReleaseForm() и GetMassGrams() возвращают верные значения. */
        TEST_METHOD(Ointment_GetReleaseForm_ReturnsMaz)
        {
            Ointment o("Финалгон", Date(2027, 1, 1), "аннотация", 320.0, "БИ",
                std::vector<std::string>{"боль в мышцах"}, 20.0);
            Assert::AreEqual(std::string("Мазь"), o.GetReleaseForm());
            Assert::AreEqual(20.0, o.GetMassGrams(), 0.0001);
        }

        /** @brief Injection::GetReleaseForm() и GetAmpoulesPerPack() возвращают верные значения. */
        TEST_METHOD(Injection_GetReleaseForm_ReturnsAmpuly)
        {
            Injection i("Диклофенак", Date(2027, 1, 1), "аннотация", 150.0, "Хемофарм",
                std::vector<std::string>{"воспаление"}, 3.0, 5);
            Assert::AreEqual(std::string("Ампулы (раствор для инъекций)"), i.GetReleaseForm());
            Assert::AreEqual(5, i.GetAmpoulesPerPack());
        }

        /** @brief TreatsDisease() возвращает true для болезни, присутствующей в списке. */
        TEST_METHOD(TreatsDisease_KnownDisease_ReturnsTrue)
        {
            Tablets t("Парацетамол", Date(2027, 1, 1), "аннотация", 45.50, "Фармстандарт",
                std::vector<std::string>{"простуда", "головная боль"}, 500.0, 20);
            Assert::IsTrue(t.TreatsDisease("головная боль"));
        }

        /** @brief TreatsDisease() возвращает false для болезни, отсутствующей в списке. */
        TEST_METHOD(TreatsDisease_UnknownDisease_ReturnsFalse)
        {
            Tablets t("Парацетамол", Date(2027, 1, 1), "аннотация", 45.50, "Фармстандарт",
                std::vector<std::string>{"простуда"}, 500.0, 20);
            Assert::IsFalse(t.TreatsDisease("ангина"));
        }

        /** @brief IsExpired() возвращает true, если срок годности уже в прошлом. */
        TEST_METHOD(IsExpired_PastDate_ReturnsTrue)
        {
            Tablets t("Старое лекарство", Date(2020, 1, 1), "аннотация", 10.0, "X",
                std::vector<std::string>{}, 100.0, 5);
            Assert::IsTrue(t.IsExpired(Date(2026, 9, 16)));
        }

        /** @brief IsExpired() возвращает false, если срок годности ещё в будущем. */
        TEST_METHOD(IsExpired_FutureDate_ReturnsFalse)
        {
            Tablets t("Свежее лекарство", Date(2030, 1, 1), "аннотация", 10.0, "X",
                std::vector<std::string>{}, 100.0, 5);
            Assert::IsFalse(t.IsExpired(Date(2026, 9, 16)));
        }

        /**
         * @brief Вызов GetInfo() через указатель базового класса
         *        (Medicine*) вызывает переопределения производного
         *        класса (полиморфизм) и включает в описание как
         *        название лекарства, так и его форму выпуска.
         */
        TEST_METHOD(GetInfo_PolymorphicCallThroughBasePointer_IncludesNameAndForm)
        {
            std::shared_ptr<Medicine> m = std::make_shared<Syrup>(
                "Пертуссин", Date(2027, 1, 1), "аннотация", 85.30, "Флора",
                std::vector<std::string>{"кашель"}, 125.0);

            std::string info = m->GetInfo();
            Assert::IsTrue(info.find("Пертуссин") != std::string::npos);
            Assert::IsTrue(info.find("Сироп") != std::string::npos);
        }
    };

    // ==== Тесты класса Pharmacy - трёх заданий варианта "Аптека" ====

    namespace
    {
        // "Сегодня" для тестов - та же дата, что используется в демо
        // консольного приложения (AptekaApp/main.cpp), чтобы комментарии
        // про "N дней назад" совпадали в обоих местах.
        const Date kToday(2026, 9, 16);

        /**
         * @brief Формирует небольшую тестовую аптеку с двумя лекарствами
         *        и несколькими продажами на известные даты/количества;
         *        переиспользуется каждым тестом в этом файле.
         * @return Готовый к запросам экземпляр Pharmacy.
         */
        Pharmacy BuildSamplePharmacy()
        {
            Pharmacy pharmacy("Тестовая аптека");

            auto paracetamol = std::make_shared<Tablets>(
                "Парацетамол", Date(2027, 1, 1), "аннотация", 45.50, "Фармстандарт",
                std::vector<std::string>{"простуда", "головная боль"}, 500.0, 20);
            auto syrup = std::make_shared<Syrup>(
                "Доктор МОМ", Date(2027, 1, 1), "аннотация", 210.00, "Юник",
                std::vector<std::string>{"кашель"}, 100.0);

            pharmacy.AddMedicine(paracetamol);
            pharmacy.AddMedicine(syrup);

            pharmacy.RegisterSale(Sale("Парацетамол", Date(2026, 9, 14), 3, 136.50)); // 2 дня назад  -> неделя
            pharmacy.RegisterSale(Sale("Парацетамол", Date(2026, 8, 25), 5, 227.50)); // 22 дня назад -> месяц
            pharmacy.RegisterSale(Sale("Парацетамол", Date(2024, 5, 1), 1, 45.50));   // больше года назад

            return pharmacy;
        }
    }

    TEST_CLASS(PharmacyTests)
    {
    public:
        // ---- Задание 1: данные о лекарствах ----

        /** @brief GetAllMedicines() возвращает все добавленные лекарства. */
        TEST_METHOD(GetAllMedicines_ReturnsAllAdded)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            Assert::AreEqual(static_cast<size_t>(2), pharmacy.GetAllMedicines().size());
        }

        /** @brief FindMedicineByName() находит существующее название независимо от регистра. */
        TEST_METHOD(FindMedicineByName_ExistingCaseInsensitive_ReturnsMedicine)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto found = pharmacy.FindMedicineByName("парацетамол");
            Assert::IsNotNull(found.get());
            Assert::AreEqual(std::string("Парацетамол"), found->GetName());
        }

        /** @brief FindMedicineByName() возвращает nullptr для незарегистрированного названия. */
        TEST_METHOD(FindMedicineByName_Missing_ReturnsNullptr)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto found = pharmacy.FindMedicineByName("Аспирин");
            Assert::IsNull(found.get());
        }

        // ---- Задание 2: продажи за период ----

        /** @brief В недельный отчёт попадает только самая свежая продажа. */
        TEST_METHOD(GetSalesForPeriod_Week_OnlyRecentSaleIncluded)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto sales = pharmacy.GetSalesForPeriod("Парацетамол", SalesPeriod::Week, kToday);
            Assert::AreEqual(static_cast<size_t>(1), sales.size());
            Assert::AreEqual(3, sales[0].GetQuantity());
        }

        /** @brief В месячный отчёт попадают и недельная, и месячная продажи. */
        TEST_METHOD(GetSalesForPeriod_Month_IncludesWeekAndMonthSales)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto sales = pharmacy.GetSalesForPeriod("Парацетамол", SalesPeriod::Month, kToday);
            Assert::AreEqual(static_cast<size_t>(2), sales.size());
        }

        /** @brief В годовой отчёт не попадает продажа старше 365 дней. */
        TEST_METHOD(GetTotalQuantitySold_Year_ExcludesOlderThanYear)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            int total = pharmacy.GetTotalQuantitySold("Парацетамол", SalesPeriod::Year, kToday);
            // Учитываются продажи 2026-09-14 (3 шт) и 2026-08-25 (5 шт) = 8;
            // продажа 2024-05-01 старше года и не учитывается.
            Assert::AreEqual(8, total);
        }

        /** @brief GetTotalRevenue() суммирует ожидаемую сумму для недельного отчёта. */
        TEST_METHOD(GetTotalRevenue_Week_MatchesExpectedSum)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            double revenue = pharmacy.GetTotalRevenue("Парацетамол", SalesPeriod::Week, kToday);
            Assert::AreEqual(136.50, revenue, 0.001);
        }

        /** @brief GetSalesForPeriod() возвращает пустой результат для неизвестного названия лекарства. */
        TEST_METHOD(GetSalesForPeriod_UnknownMedicine_ReturnsEmpty)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto sales = pharmacy.GetSalesForPeriod("Аспирин", SalesPeriod::Year, kToday);
            Assert::IsTrue(sales.empty());
        }

        // ---- Задание 3: лекарства для выбранной болезни ----

        /** @brief GetMedicinesForDisease() находит лекарство, применяемое при указанной болезни. */
        TEST_METHOD(GetMedicinesForDisease_MatchingDisease_ReturnsMedicine)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto found = pharmacy.GetMedicinesForDisease("кашель");
            Assert::AreEqual(static_cast<size_t>(1), found.size());
            Assert::AreEqual(std::string("Доктор МОМ"), found[0]->GetName());
        }

        /** @brief GetMedicinesForDisease() возвращает пустой результат, если ни одно лекарство не подходит. */
        TEST_METHOD(GetMedicinesForDisease_NoMatch_ReturnsEmpty)
        {
            Pharmacy pharmacy = BuildSamplePharmacy();
            auto found = pharmacy.GetMedicinesForDisease("перелом");
            Assert::IsTrue(found.empty());
        }
    };
}

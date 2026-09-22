#pragma once
//
// Pharmacy.h
// Класс "Аптека" - справочник лекарств плюс журнал продаж. Реализует
// три задания варианта "Аптека":
//   1) Выдавать данные о лекарствах.
//   2) Выдавать информацию о продажах покупателям за неделю (месяц, год)
//      данного лекарства.
//   3) Выдавать список лекарств, применяемых при выбранной болезни
//      (лёгком недуге).
//
#include <memory>
#include <string>
#include <vector>
#include "Medicine.h"
#include "Sale.h"
#include "SalesPeriod.h"
#include "Date.h"

/**
 * @brief Объединяет справочник лекарств именованной аптеки и её журнал
 *        продаж, отвечая на три доменных запроса, требуемых вариантом
 *        задания "Аптека".
 */
class Pharmacy {
public:
    /**
     * @brief Создаёт пустую аптеку с заданным отображаемым названием.
     * @param name Человекочитаемое название аптеки.
     */
    explicit Pharmacy(std::string name);

    /** @brief Возвращает отображаемое название аптеки. */
    const std::string& GetName() const;

    /**
     * @brief Добавляет лекарство в справочник.
     * @param medicine Умный указатель на экземпляр Medicine (или
     *                 класса-наследника) для регистрации.
     */
    void AddMedicine(std::shared_ptr<Medicine> medicine);

    /**
     * @brief Добавляет запись о продаже в журнал продаж.
     * @param sale Продажа для регистрации.
     */
    void RegisterSale(const Sale& sale);

    // ---- Задание 1: данные о лекарствах ----

    /** @brief Возвращает все лекарства, находящиеся в справочнике. */
    const std::vector<std::shared_ptr<Medicine>>& GetAllMedicines() const;

    /**
     * @brief Ищет лекарство по названию (регистронезависимо, с учётом UTF-8).
     * @param name Название лекарства для поиска.
     * @return Умный указатель на найденное лекарство, либо nullptr,
     *         если лекарство с таким названием не зарегистрировано.
     */
    std::shared_ptr<Medicine> FindMedicineByName(const std::string& name) const;

    // ---- Задание 2: продажи за период ----

    /**
     * @brief Возвращает все продажи указанного лекарства за период,
     *        заканчивающийся датой @p asOf (включительно).
     * @param medicineName Название лекарства, по которому формируется отчёт.
     * @param period       Отчётный период (неделя/месяц/год).
     * @param asOf         Опорная дата, от которой отсчитывается период
     *                     (как правило - текущая дата).
     * @return Все подходящие продажи, в произвольном порядке.
     */
    std::vector<Sale> GetSalesForPeriod(const std::string& medicineName,
        SalesPeriod period,
        const Date& asOf) const;

    /**
     * @brief Суммирует количество по всем продажам, которые вернул бы
     *        GetSalesForPeriod() с теми же аргументами.
     * @param medicineName Название лекарства, по которому формируется отчёт.
     * @param period       Отчётный период (неделя/месяц/год).
     * @param asOf         Опорная дата, от которой отсчитывается период.
     * @return Суммарное количество проданных единиц за период.
     */
    int GetTotalQuantitySold(const std::string& medicineName,
        SalesPeriod period,
        const Date& asOf) const;

    /**
     * @brief Суммирует стоимость по всем продажам, которые вернул бы
     *        GetSalesForPeriod() с теми же аргументами.
     * @param medicineName Название лекарства, по которому формируется отчёт.
     * @param period       Отчётный период (неделя/месяц/год).
     * @param asOf         Опорная дата, от которой отсчитывается период.
     * @return Суммарная выручка за период.
     */
    double GetTotalRevenue(const std::string& medicineName,
        SalesPeriod period,
        const Date& asOf) const;

    // ---- Задание 3: лекарства для выбранной болезни ----

    /**
     * @brief Находит все лекарства, применяемые при указанной болезни/недуге.
     * @param disease Название болезни/недуга для поиска (регистронезависимо).
     * @return Все подходящие лекарства, в порядке следования в справочнике.
     */
    std::vector<std::shared_ptr<Medicine>> GetMedicinesForDisease(const std::string& disease) const;

private:
    std::string name_;
    std::vector<std::shared_ptr<Medicine>> medicines_;
    std::vector<Sale> sales_;

    /**
     * @brief Возвращает длину указанного отчётного периода в днях
     *        (7 для недели, 30 для месяца, 365 для года).
     */
    static int PeriodLengthDays(SalesPeriod period);

    /**
     * @brief Проверяет, попадает ли @p saleDate в окно из @p period дней
     *        перед (и включая) дату @p asOf.
     */
    bool IsWithinPeriod(const Date& saleDate, const Date& asOf, SalesPeriod period) const;
};

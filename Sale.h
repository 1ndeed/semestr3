#pragma once
//
// Sale.h
// Класс "Продажа" - запись об одной продаже лекарства покупателю.
// Используется классом Pharmacy для построения отчётов о продажах за
// неделю/месяц/год (задание 2 варианта "Аптека").
//
#include <string>
#include "Date.h"

/**
 * @brief Неизменяемая запись об одной продаже: какое лекарство продано,
 *        в какую дату, в каком количестве и на какую общую сумму.
 */
class Sale {
public:
    /**
     * @brief Создаёт запись о продаже.
     * @param medicineName Название проданного лекарства (совпадает с Medicine::GetName()).
     * @param saleDate     Дата продажи.
     * @param quantity     Количество проданных единиц.
     * @param totalPrice   Общая сумма, уплаченная за эту продажу (все единицы).
     */
    Sale(std::string medicineName, Date saleDate, int quantity, double totalPrice);

    /** @brief Возвращает название проданного лекарства. */
    const std::string& GetMedicineName() const;

    /** @brief Возвращает дату продажи. */
    const Date& GetSaleDate() const;

    /** @brief Возвращает количество проданных единиц. */
    int GetQuantity() const;

    /** @brief Возвращает общую сумму, уплаченную за продажу. */
    double GetTotalPrice() const;

    /**
     * @brief Формирует однострочное человекочитаемое описание продажи
     *        (дата, название лекарства, количество, сумма). Потоки
     *        ввода-вывода не используются - вызывающий код сам печатает
     *        возвращённую строку.
     * @return Отформатированное описание продажи.
     */
    std::string GetInfo() const;

private:
    std::string medicineName_;
    Date saleDate_;
    // Инициализаторы по умолчанию - защита от забытого поля в будущем конструкторе.
    int quantity_ = 0;
    double totalPrice_ = 0.0;
};

#pragma once
//
// Medicine.h
// Базовый класс "Лекарство" справочника аптеки.
//
// Важно: библиотека нигде не использует потоки ввода-вывода (<iostream>,
// <fstream>, <sstream> и т.п.) - весь вывод собирается в обычные
// std::string и печатается вызывающим кодом (см. AptekaApp/main.cpp).
//
// Общие поля (по описанию предметной области "Аптека"): название, форма
// выпуска, срок годности, аннотация, цена, изготовитель. Форма выпуска
// реализована через полиморфизм: каждый класс-наследник (Tablets, Syrup,
// Ointment, Injection) переопределяет GetReleaseForm() и добавляет
// собственные поля, специфичные для этой формы выпуска.
//
#include <string>
#include <vector>
#include "Date.h"

/**
 * @brief Базовый класс, представляющий одно лекарство в справочнике
 *        аптеки. Хранит поля, общие для всех форм выпуска, и объявляет
 *        точки расширения (GetReleaseForm / GetSpecificInfo), которые
 *        классы-наследники переопределяют, добавляя собственные данные,
 *        специфичные для формы выпуска.
 */
class Medicine {
public:
    /**
     * @brief Создаёт лекарство с его общими атрибутами.
     * @param name           Торговое название лекарства.
     * @param expirationDate Срок годности.
     * @param annotation     Свободный текст описания/аннотации.
     * @param price          Цена в местной валюте.
     * @param manufacturer   Название изготовителя.
     * @param diseases       Болезни/недуги, при которых применяется лекарство.
     */
    Medicine(std::string name,
        Date expirationDate,
        std::string annotation,
        double price,
        std::string manufacturer,
        std::vector<std::string> diseases);

    /** @brief Виртуальный деструктор, необходим для полиморфных базовых классов. */
    virtual ~Medicine() = default;

    /** @brief Возвращает торговое название лекарства. */
    const std::string& GetName() const;

    /** @brief Возвращает срок годности. */
    const Date& GetExpirationDate() const;

    /** @brief Возвращает текст аннотации/описания. */
    const std::string& GetAnnotation() const;

    /** @brief Возвращает цену в местной валюте. */
    double GetPrice() const;

    /** @brief Возвращает название изготовителя. */
    const std::string& GetManufacturer() const;

    /** @brief Возвращает список болезней/недугов, при которых применяется лекарство. */
    const std::vector<std::string>& GetDiseases() const;

    /**
     * @brief Проверяет, истёк ли срок годности лекарства по состоянию на @p asOf.
     * @param asOf Дата, относительно которой проверяется срок годности
     *             (обычно текущая дата).
     * @return true, если лекарство просрочено по состоянию на @p asOf.
     */
    bool IsExpired(const Date& asOf) const;

    /**
     * @brief Проверяет, применяется ли лекарство при указанной болезни.
     *        Сравнение регистронезависимое (с учётом UTF-8, см.
     *        FormatUtils::EqualsIgnoreCase).
     * @param disease Название болезни/недуга для поиска.
     * @return true, если @p disease присутствует в списке болезней лекарства.
     */
    bool TreatsDisease(const std::string& disease) const;

    /**
     * @brief Возвращает человекочитаемое название формы выпуска.
     *        Переопределяется в каждом классе-наследнике. Значения на
     *        русском языке (например, "Таблетки" для таблеток) - как и
     *        всё содержимое и вывод программы; в комментариях к каждому
     *        наследнику дан английский перевод для справки.
     * @return Название формы выпуска.
     */
    virtual std::string GetReleaseForm() const = 0;

    /**
     * @brief Формирует однострочное человекочитаемое описание лекарства:
     *        общие поля плюс поля, специфичные для формы выпуска
     *        (через GetSpecificInfo()). Это реализация задания 1
     *        ("выдавать данные о лекарствах") варианта "Аптека".
     * @return Отформатированная строка с описанием (без завершающего перевода строки).
     */
    virtual std::string GetInfo() const;

protected:
    /**
     * @brief Возвращает часть описания, специфичную для формы выпуска
     *        (например, дозировку и количество в упаковке для Tablets).
     *        Реализуется в каждом классе-наследнике.
     * @return Короткая строка с деталями, специфичными для формы выпуска.
     */
    virtual std::string GetSpecificInfo() const = 0;

private:
    std::string name_;
    Date expirationDate_;
    std::string annotation_;
    double price_ = 0.0; // инициализатор по умолчанию - защита от забытого поля в будущем конструкторе
    std::string manufacturer_;
    std::vector<std::string> diseases_;
};

#pragma once
//
// Tablets.h
// Класс-наследник "Таблетки" - лекарство в форме таблеток.
// Дополнительные (специфичные для формы выпуска) поля: дозировка одной
// таблетки (мг) и количество таблеток в упаковке.
//
#include "Medicine.h"

/**
 * @brief Лекарство в форме таблеток. Добавляет к общим полям Medicine
 *        дозировку (мг на таблетку) и размер упаковки (таблеток в упаковке).
 */
class Tablets : public Medicine {
public:
    /**
     * @brief Создаёт лекарство в форме таблеток.
     * @param name             Торговое название.
     * @param expirationDate   Срок годности.
     * @param annotation       Текст описания.
     * @param price            Цена в местной валюте.
     * @param manufacturer     Название изготовителя.
     * @param diseases         Болезни/недуги, при которых применяется лекарство.
     * @param dosageMg         Дозировка одной таблетки, в миллиграммах.
     * @param tabletsPerPack   Количество таблеток в одной упаковке.
     */
    Tablets(std::string name,
        Date expirationDate,
        std::string annotation,
        double price,
        std::string manufacturer,
        std::vector<std::string> diseases,
        double dosageMg,
        int tabletsPerPack);

    /** @brief Возвращает дозировку одной таблетки, в миллиграммах. */
    double GetDosageMg() const;

    /** @brief Возвращает количество таблеток в упаковке. */
    int GetTabletsPerPack() const;

    /** @brief Возвращает название формы выпуска: "Таблетки" ("Tablets"). */
    std::string GetReleaseForm() const override;

protected:
    /** @brief Возвращает короткую строку с дозировкой и размером упаковки. */
    std::string GetSpecificInfo() const override;

private:
    double dosageMg_;
    int tabletsPerPack_;
};

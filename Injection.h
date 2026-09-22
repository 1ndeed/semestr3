#pragma once
//
// Injection.h
// Класс-наследник "Ампулы" - раствор для инъекций в ампулах.
// Дополнительные поля: объём одной ампулы (мл) и количество ампул в упаковке.
//
#include "Medicine.h"

/**
 * @brief Лекарство в форме ампулированного раствора для инъекций.
 *        Добавляет к общим полям Medicine объём одной ампулы (в
 *        миллилитрах) и размер упаковки (ампул в упаковке).
 */
class Injection : public Medicine {
public:
    /**
     * @brief Создаёт лекарство в форме раствора для инъекций.
     * @param name             Торговое название.
     * @param expirationDate   Срок годности.
     * @param annotation       Текст описания.
     * @param price            Цена в местной валюте.
     * @param manufacturer     Название изготовителя.
     * @param diseases         Болезни/недуги, при которых применяется лекарство.
     * @param ampouleVolumeMl  Объём одной ампулы, в миллилитрах.
     * @param ampoulesPerPack  Количество ампул в одной упаковке.
     */
    Injection(std::string name,
        Date expirationDate,
        std::string annotation,
        double price,
        std::string manufacturer,
        std::vector<std::string> diseases,
        double ampouleVolumeMl,
        int ampoulesPerPack);

    /** @brief Возвращает объём одной ампулы, в миллилитрах. */
    double GetAmpouleVolumeMl() const;

    /** @brief Возвращает количество ампул в упаковке. */
    int GetAmpoulesPerPack() const;

    /**
     * @brief Возвращает название формы выпуска: "Ампулы (раствор для
     *        инъекций)" ("Ampoules (injection solution)").
     */
    std::string GetReleaseForm() const override;

protected:
    /** @brief Возвращает короткую строку с объёмом ампулы и размером упаковки. */
    std::string GetSpecificInfo() const override;

private:
    double ampouleVolumeMl_;
    int ampoulesPerPack_;
};

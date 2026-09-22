#pragma once
//
// Syrup.h
// Класс-наследник "Сироп" - жидкое лекарство во флаконе.
// Дополнительное поле: объём флакона в миллилитрах.
//
#include "Medicine.h"

/**
 * @brief Лекарство в форме сиропа/жидкой микстуры. Добавляет к общим
 *        полям Medicine объём флакона (в миллилитрах).
 */
class Syrup : public Medicine {
public:
    /**
     * @brief Создаёт лекарство в форме сиропа.
     * @param name           Торговое название.
     * @param expirationDate Срок годности.
     * @param annotation     Текст описания.
     * @param price          Цена в местной валюте.
     * @param manufacturer   Название изготовителя.
     * @param diseases       Болезни/недуги, при которых применяется лекарство.
     * @param volumeMl       Объём флакона, в миллилитрах.
     */
    Syrup(std::string name,
        Date expirationDate,
        std::string annotation,
        double price,
        std::string manufacturer,
        std::vector<std::string> diseases,
        double volumeMl);

    /** @brief Возвращает объём флакона, в миллилитрах. */
    double GetVolumeMl() const;

    /** @brief Возвращает название формы выпуска: "Сироп" ("Syrup"). */
    std::string GetReleaseForm() const override;

protected:
    /** @brief Возвращает короткую строку с объёмом флакона. */
    std::string GetSpecificInfo() const override;

private:
    double volumeMl_;
};
